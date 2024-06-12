import time
import struct
from pyb import UART
from machine import LED
import sensor
import math
import image

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA)
sensor.skip_frames(time=2000)
sensor.set_auto_gain(False)  # must turn this off to prevent image washout...
sensor.set_auto_whitebal(False)  # must turn this off to prevent image washout...
clock = time.clock()
sensor.set_framerate(10)

led1 = LED("LED_GREEN")
led2 = LED("LED_RED")
# Initialize UART 3 with baud rate 115200
uart = UART(3, 115200)

# Initialize distance and angle
distance = 0.0
angle = 0.0
old_distance = 0.0
old_angle = 0.0

panic = 0.0

# Initialize a variable to store the time of the last detection
last_detection_time = time.ticks_ms()

# Note! Unlike find_qrcodes the find_apriltags method does not need lens correction on the image to work.

# What's the difference between tag families? Well, for example, the TAG16H5 family is effectively
# a 4x4 square tag. So, this means it can be seen at a longer distance than a TAG36H11 tag which
# is a 6x6 square tag. However, the lower H value (H5 versus H11) means that the false positive
# rate for the 4x4 tag is much, much, much, higher than the 6x6 tag. So, unless you have a
# reason to use the other tags families just use TAG36H11 which is the default family.

# The AprilTags library outputs the pose information for tags. This is the x/y/z translation and
# x/y/z rotation. The x/y/z rotation is in radians and can be converted to degrees. As for
# translation the units are dimensionless and you must apply a conversion function.

# f_x is the x focal length of the camera. It should be equal to the lens focal length in mm
# divided by the x sensor size in mm times the number of pixels in the image.
# The below values are for the OV7725 camera with a 2.8 mm lens.

# f_y is the y focal length of the camera. It should be equal to the lens focal length in mm
# divided by the y sensor size in mm times the number of pixels in the image.
# The below values are for the OV7725 camera with a 2.8 mm lens.

# c_x is the image x center position in pixels.
# c_y is the image y center position in pixels.

f_x = (2.8 / 3.984) * 160  # find_apriltags defaults to this if not set
f_y = (2.8 / 2.952) * 120  # find_apriltags defaults to this if not set
c_x = 160 * 0.5  # find_apriltags defaults to this if not set (the image.w * 0.5)
c_y = 120 * 0.5  # find_apriltags defaults to this if not set (the image.h * 0.5)


def degrees(radians):
    return (180 * radians) / math.pi


while True:
    clock.tick()
    img = sensor.snapshot()


    detected_tags = img.find_apriltags(families=image.TAG16H5, fx=f_x, fy=f_y, cx=c_x, cy=c_y)
    if len(detected_tags) == 0:
        # If no tags are detected, calculate the time since the last detection
        current_time = time.ticks_ms()
        time_since_last_detection = time.ticks_diff(current_time, last_detection_time)

        # Check if the time since the last detection is greater than 1000 ms (1 second)
        if time_since_last_detection > 1000:
            print("No AprilTag detected for longer than 1 second. Sending UART panic.")
            last_detection_time = current_time
            led1.off()
            led2.on()
            buf = struct.pack('ff', panic, panic)
            # PANIC send 0s over uart
            uart.write(buf)
    else:
        led2.off()
        led1.on()
        last_detection_time = time.ticks_ms()
        for tag in detected_tags:
            img.draw_rectangle(tag.rect(), color=(255, 0, 0))
            img.draw_cross(tag.cx(), tag.cy(), color=(0, 255, 0))
            print_args = (
                tag.x_translation(),
                tag.y_translation(),
                tag.z_translation(),
                degrees(tag.x_rotation()),
                degrees(tag.y_rotation()),
                degrees(tag.z_rotation()),
            )
        # Translation units are unknown. Rotation units are in degrees.
        # print("Tx: %f, Ty %f, Tz %f, Rx %f, Ry %f, Rz %f" % print_args)

        # Calculate the angle using inverse tangent
        angle = math.atan2( tag.x_translation(),-tag.z_translation())
        distance = tag.z_translation()
        # print("Angle:", angle)


        if(abs(distance - old_distance) > 1 or abs(angle - old_angle) > 0.05):
            # Pack the floats into bytes
            buf = struct.pack('ff', distance, angle)
            print("transmit")
            # Transmit the packed bytes over UART
            uart.write(buf)
            old_distance = distance
            old_angle = angle

    #print(clock.fps())

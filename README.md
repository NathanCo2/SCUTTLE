# SCUTTLE
ME507 Term Project

The purpose of this memo is to summarize our term project for ME 507. Our project involved the creation of a metal detecting robot, named SCUTTLE (Scavenging Utility for Trinket and Treasure Locating using Electromagnetism). This project included mechanical design, material procurement, manufacturing, PCB design, soldering, copious amounts of troubleshooting, and coding in C. The goal of the project was to create a robot that can follow a person as they walk along the beach using a machine vision camera. The robot was also intended to be able to detect metal by sweeping an arm back and forth, and to stop, locate the metal, and notify the person it is following using a buzzer when metal is detected. This memo details the mechanical, electrical, and software design of the robot, as well as the final results of the project. Attached are a video of the final functionality and a copy of the source code.


Mechanical Design

The mechanical design of the robot involves two main functionalities: driving and metal detecting. The robot must be able to traverse sandy terrain at walking speed. To achieve this, we chose to create a two-sides drivetrain with four wheels to achieve differential steering. One drive motor is implemented on each side. To drive, both motors spin forward or back. To turn, the motors are driven at different speeds, and the robot “skid-steers” by slipping to either side. To turn about a point, one motor can be driven forward and the other backwards. “Skid steering” is not very easy to model kinematically, but this is unnecessary due to the speed of the robot. Closed loop control is implemented to control the speed and orientation of the robot without the need for precise mechanical modeling. These motors were sourced from Pololu, with built in 48 CPR encoders. We originally chose 20.4:1 gearboxes but found that the motors did not have enough torque to reliably steer at low speeds. Instead, we implemented 227:1 gearboxes which we had from a previous project. These gearboxes allowed for responsive turning, but were slightly too slow for walking speed. For future implementations of this project, we recommend using a gearbox between 75:1 and 100:1 for a desirable torque to max speed ratio. Figure 1 shows the implementation of these motors. 

![CAD](https://github.com/NathanCo2/SCUTTLE/assets/156120309/8293d7f6-936b-42b2-82cb-87f5ec497a08)

Figure 1. The mechanical design of the robot, as shown in Solidworks. This includes a view of the board in green, the battery in gray, and the two drive motors in the back. 

We designed 5.5 inch diameter paddle wheels to help with traversing sand while keeping the drive base high enough above the ground to climb small hills and traverse small obstacles in the sand. The wheels are 3D printed out of PLA to minimize weight.  The back wheels are directly driven by the motors, and a pulley system is implemented on each side of the drivetrain to drive the front wheels. This allows for a four wheel drive system that can better traverse difficult terrain. The pulleys are 3D printed out of carbon-fiber ASA. The axles are hex shafts with set screws to connect the motors. A good view of the entire drive system is shown in Figure 2. 

![Screenshot 2024-07-07 113830](https://github.com/NathanCo2/SCUTTLE/assets/156120309/a55c9a72-98a6-46c5-95db-a67f2527206c)

Figure 2. The top view of the mechanical design of the robot. 

The main structure of the robot is entirely made of 3D printed carbon fiber ASA. This is mainly because we had material leftover from our senior project. The structure is divided into three pieces, with the middle piece being the main load bearing structure. This part contains slots for hex bearings that support the drivetrain. A view of this piece mid-assembly is shown in Figure 3. The structure also contains a slot for the 5200mAh battery to be velcroed into place and standoffs to bolt on our PCB. The front and back pieces were designed to be mainly cosmetic, and were shaped to look like a pirate ship to fit the theme of treasure hunting. The front piece provides mounting for the metal detector arm, while the back is purely cosmetic and mounts a cosmetic back mast. 

![Screenshot 2024-07-07 113844](https://github.com/NathanCo2/SCUTTLE/assets/156120309/528e7ec6-37f3-47f5-abdc-b57646a9b88a)

Figure 3. The base mid-assembly, showing the hex shafts, pulleys, and belt. 

The front mast contains functionality for both vision tracking and metal detecting. We use an OpenMV camera to track an April Tag to find the distance and angle from the camera to the April Tag. This camera is mounted as high as possible at an angle, at the top of the front mast in the crows nest. The front mast also implements another Pololu motor that controls the angular position of the arm. This motor ended up having the 20.4:1 gearbox that we were intending to use on the drivetrain, as our original intended motor was swapped onto the drivetrain. For future implementation, a higher gear ratio is optimal for finer position control of the arm. The motor drives another hex shaft, which is held in place by two bronze bushings. 

A 3D printed adapter interfaces between the arm hex shaft and a PVC pipe, allowing the PVC pipe to rotate when the arm motor is driven. This PVC pipe then interfaces with a flat plate that contains our metal detector coils. The coils use magnet wire wound into 60 coils each, at a diameter of 15 cm. Figure 3 shows one of these coils mid-assembly. 

![image5 (1)](https://github.com/NathanCo2/SCUTTLE/assets/156120309/8ec07e5f-9132-48b7-a6c9-5df179045964)

Figure 4. One of the metal detector coils.
Once the coils were completed, they were wrapped in electrical tape for insulation. One of the coils was then wrapped in aluminum foil for further screening, and again wrapped in electrical tape. Figure 4 shows one of the completed coils. These coils were then zip tied to the bottom of the flat plate and overlapped. Electrical connections were soldered on and the wires were sent through the arm and interfaced with our PCB. 

![image3 (1)](https://github.com/NathanCo2/SCUTTLE/assets/156120309/db3d8523-f8f8-4504-9170-a934cc522a7f)

Figure 5. A completed metal detector coil. 

Mechanically, the robot functioned perfectly, as it was able to drive and turn, while the arm was able to rotate about 150 degrees. The camera could see a person from about 12 feet away, and the electronics were neatly implemented and protected from the bulk of the elements. A picture showing the final implementation is shown in Figure 5. 

![image1 (1)](https://github.com/NathanCo2/SCUTTLE/assets/156120309/0f2ae84a-9099-4d14-bceb-46ba02316ed7)

Figure 6. A picture of the final SCUTTLE assembly. A clear plastic cover was integrated to protect the electronics. 
 

Electrical Design 

The electrical design involved four main functions: Microcontroller implementation, voltage regulation, metal detector circuitry, and motor driver circuitry. This was almost entirely implemented on a custom built PCB. This PCB was designed in Fusion 360, using schematic and footprint files downloaded from the internet for each component. Figures 6 and 7 show the schematic and PCB layout for our design. The main sensors on this project included the metal detector circuit, OpenMV camera, and encoders on each motor. 

![image4 (1)](https://github.com/NathanCo2/SCUTTLE/assets/156120309/be1c9d7f-e40d-406a-ba59-2f9f72e8b8b3)

Figure 7. The full electrical schematic for our PCB. 

We chose an STM32L471RGT6 microcontroller, as it has just enough timer and communication pins to implement 4 motors, 4 encoders, and the necessary ADC for our metal detector. Electrically, we connected the necessary amount of filtering capacitors, and provided 3.3V power to the board. We implemented a reset switch, along with an external 25 Mhz crystal oscillator. We also routed unused pins to external headers.

To implement voltage regulation, we used a switching regulator to step down from 12V to 5V. This allows us to power our robot using an 11.1V 3S1P 5200mAh battery. An XT connector was soldered to the board to interface with this battery. The 5V was necessary to power our encoders, OpenMV camera, and the detection part of our metal detector circuitry (though we forgot to put the metal detector 5V connection in our schematic and needed to bodge wire it). We had a lot of trouble implementing our switching regulator, and ended up needing to replace the component to get it to work correctly. We used a breakout board for our 5V line for much of our debugging, but was able to solder on a working switching regulator the night before the demo. We used a linear regulator to step down from 5V to 3.3V. This was necessary to power our microcontroller. 

![image6 (1)](https://github.com/NathanCo2/SCUTTLE/assets/156120309/4661e060-5728-4bed-9081-8ef6797d3a16)

Figure 8. The electrical full PCB layout of SCUTTLE. 

Two L6226QTR motor driver chips were implemented based on the datasheet. These motor drivers allowed us to use the microcontroller to spin two motors on each chip based on PWM inputs. We chose to implement the ability to drive four motors for redundancy and so that more motors could be implemented on the board for future projects. We misread the datasheet and mixed up the functionality of some of the motor outputs, but fortunately this mistake was easily fixed by switching some of the motor wires without modifying the board. This would need to be changed on a future iteration of this project. Four 6 pin headers were implemented to connect our motor leads and each encoder. 

Finally, the metal detector circuitry was copied from a tutorial in the following link: https://www.hackster.io/mircemk/diy-sensitive-arduino-ib-metal-detector-d5e029. This metal detector used ADC and GPIO pins on an Arduino to drive the metal detector, along with an assortment of transistors, resistors, and capacitors to read and amplify the signal. Two potentiometers are used to adjust the metal detector’s sensitivity and pulse timing. We provided headers on our board in order to interface these potentiometers in a more easily accessible position on our robot. We also implemented headers to connect the coils to our board. There were multiple mistakes with implementing this circuit that had to be manually fixed by rerouting pins and bodge wiring components on the board. This included connecting the wrong pins on a transistor and forgetting to connect 5V to the potentiometers.  We unfortunately ran out of time to test the metal detector, though the electrical and mechanical design is fully complete, and the metal detector code is written. 

Other miscellaneous functionality includes a voltage divider to measure the battery voltage level using an ADC pin (which has been tested and works), and reverse current protection using a PMOSFET. A fuse is implemented for overcurrent protection. Header pins are provided for multiple types of communication protocol in case they were necessary, and we ended up using the UART pins to communicate with the OpenMV camera instead of the originally planned SPI. Finally, header pins for input capture of a remote control were implemented to create an emergency stop if the remote controller trigger was not pressed. While we were able to read the remote control, we were unable to get the Estop to multitask properly in time for our demo. Due to the low speed of our project, we decided to demo without the estop as the robot was very safe and easy to pick up. We also implemented a hard stop with our OpenMV camera. If the camera did not see the April Tag, the robot would automatically shut off all motors. 

As this was our first attempt at designing a PCB, there were naturally a few mistakes. We had a few electrical mishaps along the way and had to spend a lot of time soldering bodge wires to debug, tombstoning components that were wired improperly, and even hand soldering on a new MCU. 

Ultimately, we spent a large amount of time on the design, soldering, and troubleshooting of our board. We are incredibly happy to report that with some slight modifications, our board was fully functional, and we were able to use it with our battery during the demo of our robot. A picture of our board is shown in Figure 8. 

Figure 8. Our fully assembled PCB. 


Software Implementation

Our project was coded in C using STM32CubeIDE. Drivers were built for our motors, encoders, and OpenMV data processing. Code was then flashed to board using an STLink from a Nucleo. Debugging was done using the Serial Wire Output pin which allowed us to read real time data from the MCU during testing. All code has been documented on GitHub pages and can be found at the following link: https://nathanco2.github.io/SCUTTLE/

Drivers were built for both the motors and encoders. The motors require two PWM outputs to drive and brake. Each encoder required two channels on their own timer for proper reading. The motor driver directly updates the relevant autoreload registers affiliated with the timer pointers, and a set_duty() function is used to drive the motors using a duty percentage found with the period pointer within the timer. The encoder was configured using the .ioc file for the project and setting the proper timer up in encoder mode. This allowed us to read the encoder whenever we wanted to be implemented in the control loop. The read_encoder() function updates the relevant encoder object with velocity and position values to be used by the motor control loop.

The motor controller for the differential steering is implemented using PI control on the velocity reading from the encoder. Timing is stored within the relevant motor controller pseudo object for the integration control to work properly. Gains for both motors were found experimentally, and did not require fine optimization as the system does not need a fast reaction speed.

The OpenMV camera uses a built-in library to read a 16 square April Tag in its field of view. We chose to use a low resolution April Tag as it allows for any light conditions, skew resistance, and reading from a further distance. It returns the x and y location in the FOV of the April Tag and finds a distance value based on built in focal point calculations. We use the x and z values to calculate the relative angle of the april tag to the center of the FOV. These two float setpoints are then packaged and sent through UART to the MCU which reads and processes the data in a non-blocking manner using interrupts. The on board LED turns green when it sees an April Tag and red when it can’t find one. When the OpenMV camera does not find an April Tag in its FOV, after a set time it will send a panic flag (all zeroes) to the MCU through UART. The main control loop will then set the velocity setpoint to zero and bring SCUTTLE to a halt.

The system control loop was implemented within the motor control task. Every time it is run it updates the velocity and distance setpoints using the values given through UART. Proportional control was used to relate the distance setpoint to the two motors' velocity setpoints. The angle measurement added magnitude to one motor’s velocity setpoint and subtracted magnitude from the other motor’s velocity setpoint. These proportional gains were also found experimentally.

This code was successful in reading an April Tag at a distance and updating its motors accordingly. It is capable of being implemented into a multitasking system. We attempted to build a finite state machine capable of driving all the motors, metal detecting module, and Estop, but had to reduce scope due to timing constraints. Each task has been written and documented in the page's link. Each task is separated into its own .c file for easier modularity. Functions were called from the main loop that passed in the relevant variables to each task.

Due to the limited time we had to code and test our robot, there was a lot of code that was written and tested but not fully implemented into our final demo. Our vision for the software was to have six tasks that run in succession. The main loop is a switch case that circles through each task, which calls a function that runs a finite state machine in each task. In this way, we have six different state machines that run successively, and that we could code and test completely separately from each other. This theoretically makes debugging, testing and compartmentalizing code much easier, while also making it easier to edit code as each task is contained in its own .c and .h file. However, we ran into issues with the error handler being triggered when going between different tasks. We did not have time to find the solution to this (we found this problem at 3am the morning before demo), but we suspect that we are either running out of stack memory or more likely there are problems with how we are passing floats into our functions. 

The result of this software issue is that we unfortunately were only able to run one task and our main loop. All other tasks had to be commented out. This was fine for our demo, as we implemented our OpenMV sensor reading into our main file as a callback function, and only called task 6, which was our drive motor control function. This meant that despite having a working Estop for the controller in task 2, we were unable to make it work with task 6. For safety during the demo, we made sure to implement a different kind of Estop by having the motors shut off when the camera did not see an April Tag. The other functionality that was impacted by this was our battery reading in task 1, but for the demo we made sure our battery was fully charged, making this task unnecessary for short term use. Another result was that we wrote a task 3 for communication with the OpenMV camera but replaced all of its functionality. We included task 3 in our source code, but noted that it is not deprecated in the doxygen markups.  

Our task 4 and 5 contain code necessary for running the metal detector and arm motor. We ran out of time to test these tasks, and they were not used during the demo. Task 4 is theoretically finished, but it is likely that many hours of testing and debugging will be needed to have a fully functional metal detector. Task 5 is not fully implemented, but contains an outline for how to control the arm to passively sweep for metal, and to run closed loop control when metal is detected.

Ultimately, we simply ran out of time to implement the rest of our code besides our vision and drive system. We did spend a long time writing and testing this code, so we decided to discuss it even though it was not fully implemented. If we had an extra couple of weeks to work on this project, we are confident that we would have been able to solve our major software issues preventing us from using all of our taks. We would also be able to test the metal detector and implement the arm functionality to have a fully finished final product. We both hope to make a second version of the project some day, improving upon the design, fixing bugs, and finishing the code. We already have a very solid mechanical and electrical design, and mostly working code, so we are confident that the entire project scope could be successfully implemented with more time. 

Conclusion

This project was a valuable experience to instruct us how to properly implement control systems design into mechatronics projects. Though we did not complete our entire scope on the coding side, we were successful in demonstrating code flashed onto our custom designed board driving a fully manufactured robot. The learning of these concepts will enable many future projects of our own, and we were grateful to build a successful SCUTTLE. 

# CS207-Obstacle-avoiding-robot
CS207 Final Project


The aim of this project is to build the obstacle avoiding robot using the ELEGOO's "Smart Robot Car V3.0" . The main idea behind it is allowing the owner to control the robot, so that he can decide where the
robot should go, but if there is an obstacle the robot will no longer move forward, instead, the car will move
backward and change its path. And the owner will be able to control it again.


# HOW THE PROJECT WORKS
_______________________________________________________________________________________

If the project is perfectly assembled and the sketch "Obstacle_Avoidance_Car.ino" is successfully uploaded into the 
arduino board, then the steps are the following:

1. Download the application “ELEGOO BLE Tool” provided by ELEGOO and available for Android and IOS.
2. The application provides some buttons, and the user has to set the values that every button is going to represent. The user can change those values by keeping pressing any button.
3. When the user has set the values for “Forward”, “STOP” and “Back”  is  time to turn the robot battery switch on.
4. In order to establish connection with the robot is necessary to go to the top left corner with the label “Connection” and select “HC-08” from the Bluetooth devices list.
5. After selecting the Bluetooth device, the “No connection” label on top will change for the name of the Bluetooth module, which in this case is “HC-08”.
6. After following the steps mentioned before, the user will be able to control the robot.



# Avoiding stairs
There is an additional file called avoidStairs.ino which contains the code for avoiding black lines. The idea behind this sketch was
to use it to complement the Obstacle_Avoidance_Car.ino sketch, but when both codes were put together the robot didn't behave as expected.
The black lines can indicate the border of the stairs and for instance, it can help the robot to avoid them.




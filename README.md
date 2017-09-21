HexapodRobot
==============
Using Open_Hardware Raspberry pi & RoboPi

-----------------------------------------
# Hardware List
1. Raspberry pi Ver2
2. RoboPi
3. 18 * ServoMotor & stuff to fix
4. 3 * Ultrasonic Sensor
5. gyroScope Sensor
6. piCam
-----------------------------------------
# Software List
1. RoboPiLib
2. RTIMULib
3. App with SmartPhone
-----------------------------------------
# Code Explain
1. main.c : Main Algorithm for avoiding obstacle
2. movement.c : Function for moving Robot by controlling ServoMotors
3. server.c : Function for communicating with SmartPhone
4. ultraSonic.c : Function for finding obstacle around Robot
5. RTIMULibDrive.cpp : Function for getting gyro data and making information
-----------------------------------------
# algorithm 
Using Thread:
	For getting gyrosensor data 
	For getting client input

-----------------------------------------
# To do list before Using Hardware
1. piCam : enable raspi-config -> piCam
2. gyroScope : enable raspi-config -> i2c communication
3. serial communication -> serial

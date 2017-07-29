//**********************************************************************************
// RoboPiLib Serial Protocol Library For RoboPi
//
// RoboPiLib_v0.85.h
//
// Raspberry Pi / Linux support library for RoboPi firmware
//
// Copyright 2014 William Henning
//
// http://Mikronauts.com
//
//**********************************************************************************

// Pin Modes

#define INPUT 0
#define OUTPUT 1
#define PWM 16
#define SERVO 32

// Initialization

void RoboPiInit(char *device, int bps); // device = "/dev/ttyAMA0", bps = 9600..115200 matching RoboPi config
void RoboPiExit(); // close the serial device

// Setting / Reading Pin Modes

int  readMode(int pin);				// pin = 0..23, returns INPUT/OUTPUT/PWM/SERVO as defined above
void pinMode(int pin, int mode);	// pin = 0..23, mode = INPUT/OUTPUT/PWM/SERVO

// Reading / Writing Digital I/OUTPUT

int  digitalRead(int pin);			// pin = 0..23, returns 0 or 1, if pin = 24..31 returns 0 or 1 for ain0-ain7
void digitalWrite(int pin, int val);// pin = 0..23, val = 0 or 1

// Analog input 

int  analogRead(int pin); 			// returns 0..1023
int  analogReadRaw(int pin);		// returns 0..4095 with MCP3208

// PWM output

void analogWrite(int pin, int val); // val = 0..255

// Servo Functions

int  servoRead(int pin);			// returns 0..2500 microseconds
void servoWrite(int pin, int val);	// pin = 0..23, val = 0..2500 microseconds

// Distance Function

int  readDistance(int pin);		// return distance to nearest object in milimeters

// Firmware Extension

int putPacket(char cmd, char *buff, int len); // send a packet to RoboPi
int getPacket(char *cmd, char *buff, int *len); // receive a response from RoboPi

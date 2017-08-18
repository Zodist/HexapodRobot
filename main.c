#include <stdio.h>
#include "RoboPiLib.h"
#include "SetMacro.h"
#include "Server.h"

//detect object by UltraSonic Sensor
extern int detectObj();

//movement func
extern void initializePosi();
extern void stablePosi();
extern void moveForward();
extern void MoveUp(int[],int,int);
extern void MoveDown(int[], int, int);
extern void CMoveUp(int[], int, int);
extern void CMoveDown(int[], int, int);
extern void changeDir();
extern int hips;

//initializePi func is setting 'pinMode', 'RoboPiInit'
void initializePi();

//initialization function - movement, gyro, server
void initialize();

//gyro sensor
extern void gyroInit();
extern double gyroSensor();
extern void getDegree(float degree[]);
extern void storeVector();
extern void showVector();

//server
extern void serverInitialize();

void main(int argc, char **argv) {
	int i;
	int an;
	int detecResult=0;
	
	int tmp1, tmp2;
	
	/*initialize*/
	initialize();
	
	//========= TODO : Alogithm ===========//
	
	printf("moveForward? 1:yes, 0:no ");
	scanf("%d",&an);
	if(an) {
		printf("input a,b,c : ");
		scanf("%d %d %d", &tmp1, &tmp2, &hips);
		downHips(tmp1,tmp2);
		stablePosi();
		while(1) {
			moveForward();
			storeVector();
			detecResult = detectObj();
			if(detecResult) {
				printf("**Object detected!\n");
				changeDir();
				storeVector();				
				showVector();
			}else	
				printf("**Object not detected\n");
		}
	}
	stablePosi();
	RoboPiExit();
	
	//========= TODO : Alogithm ===========//
	
}
void initialize() {
	/*raspberryPi initialization*/
	initializePi();
	printf("DONE ======== raspberryPi initialization\n");

	/*gyro sensor initialization*/
	gyroInit();
	printf("DONE ======== gyro sensor initialization\n");
	printf("========================================\n");

	/*server initialization*/
	serverInitialize();
	printf("DONE ============= server initialization\n");

	printf("**initialization all ============== DONE**\n");

	/*robot position initialization*/
	initializePosi();
	printf("DONE ===== robot position initialization \n");
}
void initializePi() {
	RoboPiInit("/dev/serial0", 115200);
	pinMode(L1_1, SERVO);
	pinMode(L1_2, SERVO);
	pinMode(L1_3, SERVO);
	pinMode(L2_1, SERVO);
	pinMode(L2_2, SERVO);
	pinMode(L2_3, SERVO);
	pinMode(L3_1, SERVO);
	pinMode(L3_2, SERVO);
	pinMode(L3_3, SERVO);
	pinMode(R1_1, SERVO);
	pinMode(R1_2, SERVO);
	pinMode(R1_3, SERVO);
	pinMode(R2_1, SERVO);
	pinMode(R2_2, SERVO);
	pinMode(R2_3, SERVO);
	pinMode(R3_1, SERVO);
	pinMode(R3_2, SERVO);
	pinMode(R3_3, SERVO);
//	pinMode(miniServo, SERVO);
	printf("SETTING PIN SUCCESS\n");
}

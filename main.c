#include <pthread.h>
#include <stdio.h>
#include "RoboPiLib.h"
#include "SetMacro.h"
//#include "Server.h"

//About initialization Function========================
//initializePi func is setting 'pinMode', 'RoboPiInit'
void initializePi();

//initialization function - movement, gyro, server
void initializeAll();

//exitProcess
void exitProcess();
//=====================================================

//About Sensors Function===============================
//UltraSonic Sensor Function
extern int detecForward();
extern int detecLeft();
extern int detecRight();
//extern int detectObj();
//Gyro sensor Function
extern void setStd();//set standard axis for gyro sensor
extern void gyroInit();
extern double gyroSensor();
extern void getDegree(float degree[]);
extern void storeVector();
extern void showVector();
int moveDirection = 0;	// 0 : 직진 1:왼쪽 2:오른쪽
int startflag = 0;			// 2 일 때 출발

void* gyroThreadF(void *data) {
	while (1) {
		storeVector();
		analyVector();
	}
	return (void*)NULL;
}
//=====================================================

//Thread varaibles======================================
int gyroThreadStatus;
int serverThreadStatus;
pthread_t gyrothread;
pthread_t serverthread;
char p1[] = "gyrothread";
char p2[] = "serverthread";
//=====================================================

//Movement Function====================================
extern void initializePosi();
extern void stablePosi();
extern void moveForward();
extern void MoveUp(int[],int,int);
extern void MoveDown(int[], int, int);
extern void CMoveUp(int[], int, int);
extern void CMoveDown(int[], int, int);
extern void changeDir(int dir);
extern int hips;
//=====================================================

//Server Function======================================
extern int distance;	// 단위 : cm
extern char direction;	// 동쪽, 서쪽, 남쪽, 북쪽
const int startDir[4][2] = {{3,1},{3,0},{6,1},{0,1}}; //{turnNum,turnDir}
extern int clnt_sock;
extern void serverInitialize();
extern void *serverThreadF(void *data);
extern void WaitCameraInput();
void WaitForInput();
//=====================================================

//integrate movement
void readyForMove();
void moveToDestinationVer2();

int state = 1; //1:직진중 2:왼쪽회전 3:오른쪽회전

void startGyroThread(){
	gyroThreadStatus = pthread_create(&gyrothread, NULL, gyroThreadF, (void*)p1);
	if (gyroThreadStatus < 0) {
		printf("gyrothread create error\n");
		exit(0);
	}
}
void startServerThread(){
	serverThreadStatus = pthread_create(&serverthread, NULL, serverThreadF, (void*)p2);
	if (serverThreadStatus < 0) {
		printf("serverthread create error\n");
		exit(0);
	}
}
void main(int argc, char **argv) {
	/*initialize*/
	initializeAll();
	//========= TODO : Alogithm ===========//
	initializePosi();	/*robot position initialization*/
	/*
	startServerThread();
	WaitForInput();
	*/
	direction='n';distance=100; 	//Example Input

	readyForMove();
	startGyroThread();
	moveToDestinationVer2();
	exitProcess();
	//========= TODO : Alogithm ===========//
}
void readyForMove(){
	int i;
	int rNum = 0,rDir = 0;
	switch(direction){
	case 'e':rNum = startDir[0][0]; rDir = startDir[0][1]; break;
	case 'w':rNum = startDir[1][0]; rDir = startDir[1][1]; break;
	case 's':rNum = startDir[2][0]; rDir = startDir[2][1]; break;
	case 'n':rNum = startDir[3][0]; rDir = startDir[3][1]; break;
	default: printf("Unknown Direction\n");break;
	}
	for(i=0;i<rNum;i++){					
		changeDir(rDir);
	}
	stablePosi();
	setStd();//set standard axis for gyro sensor
}
void initializeAll() {
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
	
	printf("**initialization all ============== DONE**\n\n");
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
	printf("SETTING PIN SUCCESS\n");
}
void WaitForInput(){
	startflag = 0;
	waitForClientConnect();
	//waitForClientInput();
	while (startflag !=2 ) { usleep(500000); }
}

void moveToDestinationVer2() {
	int i;
	int dir = 0; // 0: right 1: left
	int turnNum = 2;

	while(1) {
		if (distance == 0) break;
		printf("********************moveDirection = %d\n",moveDirection);
		if (moveDirection == 0) { //직진을 해야함
			switch (state) {
			case 1: //직진중
				if (detecForward() == 0) state = 1;
				else if (detecRight() == 0) state = 3;
				else state = 2;;
				break;
			case 2: //왼쪽회전상태	// 왼쪽회전상태에서 전방과 오른쪽에 장애물 있는 경우는 고려x
				if (detecRight() == 0) state = 3;
				else if (detecForward() == 0) state = 1;
				break;
			case 3: //오른쪽회전상태
				if (detecLeft() == 0) state = 2;
				else if (detecForward() == 0) state = 1;
				break;
			}
		}
		else if (moveDirection == 1) {	//왼쪽회전 해야함
			switch (state) {
			case 1: //직진중
				if (detecLeft() == 0) state = 2;
				else if (detecForward() == 0) state = 1;
				else state = 3;
				break;
			case 2: //왼쪽회전 상태
				if (detecForward() == 0) state = 1;
				else if (detecRight() == 0) state = 3;
				break;
			case 3: //오른쪽 회전 상태
				if (detecLeft() == 0) state = 2;
				else if (detecForward() == 0) state = 1;
				break;
			}
		}
		else if (moveDirection == 2) {	//오른쪽회전 해야함
			switch (state) {
			case 1: //직진중
				if (detecRight() == 0) state = 3;
				else if (detecForward() == 0) state = 1;
				else state = 2;
				break;
			case 2: //왼쪽회전상태
				if (detecRight() == 0) state = 3;
				else if (detecForward() == 0) state = 1;
			case 3: //오른쪽회전상태
				if (detecForward() == 0) state = 1;
				else if (detecLeft() == 0) state = 2;
				break;
			}
		}
		printf("********************state = %d\n",state);
		if (state == 1) {	//직진했으면
			moveForward();
			distance -= 5;
		}
		else {
			if (state == 2) dir = 0;
			else if (state == 3) dir = 1;
			for(i = 0; i < turnNum; i++) changeDir(dir);
		}
	}
}

void exitProcess(){
    close(clnt_sock);       /* 연결 종료 */
	RoboPiExit();
	printf("============MOVEMENT IS OVER============\n");
	//pthread_exit(3); //thread종료
	//Thread 종료 대기
	//pthread_join(gyrothread, (void **)&gyroThreadStatus);
	//pthread_join(serverthread, (void **)&serverThreadStatus);
	exit(1);
}
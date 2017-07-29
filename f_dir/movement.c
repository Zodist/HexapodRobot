#include "SetMacro.h"
#include "RoboPiLib.h"
#include <stdio.h>

//setting GROUP
int axisA[3] = {L1_1, R2_1, L3_1};
int axisB[3] = {R1_1, L2_1, R3_1};
int hipA[3] = {L1_2, L3_2, R2_2};
int hipB[3] = {L2_2, R1_2, R3_2};
int legA[3] = {L1_3, R2_3, L3_3};
int legB[3] = {R1_3, L2_3, R3_3};
int position[18] = {
	1500, 900, 1000,
	1000, 1150, 1100,
	900, 900, 1350,
	1200, 1400, 1400,
	1800, 1300, 1200,
	2200, 1400, 1200
	};

int isReversed[] = {
	1, 1, 0,
	1, 1, 0,
	1, 1, 0,
	0, 0, 1,
	0, 0, 1,
	0, 0, 1
	};

void initializePosi();
void stablePosi();

int getStatus(int index);
void setStatus(int index, int posi);

void MoveUp(int IDArray[], int size, int incrPos);
void MoveDown(int IDArray[], int size, int decrPos);
void moveForward();

void CMoveUp(int IDArray[], int size, int incrPos);
void CMoveDown(int IDArray[], int size, int incrPos);
void changeDir();

void testServo();

//Movement Of Robot
int MoveRobot(){
	int move,i;
	initializePosi();
	printf("MoveForward? :(NO:0,YES:1)");
	scanf("%d",&move);
	if(move==1){
		i = 1;
		while(i<6){
			i++;
			moveForward();
			//sleep(1);
			//stablePosi();
			sleep(1);
		}
		stablePosi();
	}
	printf("ChangDirection? :(NO:0,YES:1)");
	scanf("%d",&move);
	if(move==1){
		changeDir();
		sleep(1);
	}
	testServo();
}

void testServo(){
	int i,pin;
	while(1){
		printf("Input pin,degree :");
		scanf("%d %d",&pin,&i);
		if(pin == 2000) break;
		servoWrite(pin, i);
	}
}

void CMoveUp(int IDArray[], int size, int incrPos){
	int i;
	for(i = 0; i < size; i++){
		int index = IDArray[i]; 
		int pos;
		if(1){//isReversed[index]){
			if(index==7){
				pos = getStatus(index) - incrPos -100;
			}else
				pos = getStatus(index) - incrPos;
		}else{
				pos = getStatus(index) + incrPos;
		}
		servoWrite(index, pos);
		setStatus(index, pos);
	//	printf("servo : %d -> degree : %d\n", index, pos);
		
	}
	usleep(100000);
}
void CMoveDown(int IDArray[], int size, int decrPos){
	int i;
	for(i = 0; i < size; i++){
		int index = IDArray[i];
		int pos;
		if(1){//isReversed[index]){
			if(index==7){
				pos = getStatus(index) + decrPos +100;
			}else
				pos = getStatus(index) + decrPos;
		}else{
			pos = getStatus(index) - decrPos;
		}
		servoWrite(index, pos);
		setStatus(index, pos);
	//	printf("servo : %d -> degree : %d\n", index, pos);
	}
	usleep(100000);
}

void changeDir(){
	int i;
	for(i=0;i<3;i++){
		MoveUp(hipB, 3, 500); 		//hips group B move up 100
		CMoveUp(axisA, 3, 300);	// axis group B move forward 60
		MoveDown(hipB, 3, 500);		//hips group B move down 100
		CMoveDown(axisA, 3, 300);	// axis group B move forward 60
		sleep(1);
		MoveUp(hipA, 3, 500);		//hips group A move up 100
		CMoveUp(axisB, 3, 300);		// axis group A move backward 60
		MoveDown(hipA, 3, 500);		//hips group A move up 100
		CMoveDown(axisB, 3, 300);		// axis group A move backward 60
		sleep(1);
	}
	sleep(1);
}

void moveForward(){
	MoveUp(hipB, 3, 500); 		//hips group B move up 100
	MoveDown(axisB, 3, 300);	// axis group B move forward 60
	MoveUp(axisA, 3, 300);		// axis group A move backward 60
	MoveDown(hipB, 3, 500);		//hips group B move down 100
	MoveUp(hipA, 3, 500);		//hips group A move up 100
	MoveUp(axisB, 3, 300);		// axis group B move backward 60
	MoveDown(axisA, 3, 300);	// axis group A move forward 60
	MoveDown(hipA,3, 500);		//hips group A move down 100
	sleep(1);
}


void initializePosi(){
	int init;
	int i;
	printf("Do you want to reset position? : (0:no, 1:yes)");
	scanf("%d",&init);
	if(init == 1){
		for(i=0;i<18;i++){
			servoWrite(i, position[i]);
			usleep(100000);
		}
		stablePosi();
	}
	printf("initialize Position ===== SUCCESS\n");
}

void stablePosi(){
	int i;
	for(i=0;i<18;i+=3){
		if(i<=6){
			servoWrite(i+1, position[i+1]-500);
			usleep(300000);
			servoWrite(i+2, position[i+2]+300);
			usleep(300000);
		}else{
			servoWrite(i+1, position[i+1]+500);
			usleep(300000);
			servoWrite(i+2, position[i+2]+300);
			usleep(300000);
		}
			servoWrite(i+2, position[i+2]);
			usleep(300000);
			servoWrite(i+1, position[i+1]);
			usleep(300000);
	}
}

int getStatus(int index){
	return position[index];
}

void setStatus(int index, int posi){
	position[index] = posi;
}

void MoveUp(int IDArray[], int size, int incrPos){
	int i;
	for(i = 0; i < size; i++){
		int index = IDArray[i]; 
		int pos;
		if(isReversed[index]){
			if(index==7){
				pos = getStatus(index) - incrPos -100;
			}else
				pos = getStatus(index) - incrPos;
		}else{
				pos = getStatus(index) + incrPos;
		}
		servoWrite(index, pos);
		setStatus(index, pos);
	//	printf("servo : %d -> degree : %d\n", index, pos);
		
	}
	usleep(100000);
}
void MoveDown(int IDArray[], int size, int decrPos){
	int i;
	for(i = 0; i < size; i++){
		int index = IDArray[i];
		int pos;
		if(isReversed[index]){
			if(index==7){
				pos = getStatus(index) + decrPos +100;
			}else
				pos = getStatus(index) + decrPos;
		}else{
			pos = getStatus(index) - decrPos;
		}
		servoWrite(index, pos);
		setStatus(index, pos);
	//	printf("servo : %d -> degree : %d\n", index, pos);
	}
	usleep(100000);
}

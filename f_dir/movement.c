#include "SetMacro.h"
#include "RoboPiLib.h"
#include <stdio.h>

//setting GROUP
int axisA[3] = {L1_1, R2_1, L3_1};
int axisB[3] = {R1_1, L2_1, R3_1};
int hipA[3] = {L1_2, R2_2, L3_2};
int hipB[3] = {R1_2, L2_2, R3_2};
int legA[3] = {L1_3, R2_3, L3_3};
int legB[3] = {R1_3, L2_3, R3_3};

int position2[19] = {
	1500, 1300, 1300,
	1000, 1350, 1400,
	700, 1200, 1500,
	1200, 1150, 1100,
	1800, 800, 800,
	2200, 0 ,1100, 700
	};
int position[19] = {
	1500, 1300, 1300,
	1000, 1350, 1400,
	700, 1200, 1500,
	1200, 1150, 1100,
	1800, 800, 800,
	2200, 0 ,1100, 700
	};

int isReversed[] = {
	1, 1, 0,
	1, 1, 0,
	1, 1, 0,
	0, 0, 1,
	0, 0, 1,
	0, 0, 0, 1
	};
int axis = 300;
int hips = 500; // default 500
const int t1 = 100;
const int t2 = 200;
const int t3 = 100;
const int t4 = -200;
int startmove = 0;

void initializePosi();
void stablePosi();

int getStatus(int index);
void setStatus(int index, int posi);

void LegMove(int hip[], int leg[], int index, int size, int hipd, int legd);
void MoveAxisUp(int IDArray[], int size, int incrPos);
void MoveUpHipsForReady(int hip[], int leg[], int size);
void MoveUp(int IDArray[], int size, int incrPos);
void MoveDown(int IDArray[], int size, int decrPos);
void moveForward();

void CMoveUp(int IDArray[], int size, int incrPos);
void CMoveDown(int IDArray[], int size, int incrPos);
void changeDir();

void downHips(int deg1, int deg2);
void testServo();

void downHips(int deg1, int deg2){
	int i;
	for(i=1;i<=7;i+=3){
		position[i] = position2[i]-deg1;
		servoWrite(i, position[i]);
		usleep(200000);

		position[i+1] = position2[i+1]+deg2;
		servoWrite(i+1, position[i+1]);
		usleep(200000);

	}
	for(i=10;i<=15;i+=3){
		position[i] = position2[i]+deg1;
		servoWrite(i, position[i]);
		usleep(200000);

		position[i+1] = position2[i+1]-deg2;
		servoWrite(i+1, position[i+1]);
		usleep(200000);
	}
	position[17] = position2[17]+deg1;
	servoWrite(17, position[17]);
	usleep(200000);

	position[18] = position2[18]-deg2;
	servoWrite(18, position[18]);
	usleep(200000);
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
		if(1){
			if(index==7){
				pos = getStatus(index) - incrPos -100;
			}else
				pos = getStatus(index) - incrPos;
		}else{
				pos = getStatus(index) + incrPos;
		}
		servoWrite(index, pos);
		setStatus(index, pos);
	}
	usleep(100000);
}
void CMoveDown(int IDArray[], int size, int decrPos){
	int i;
	for(i = 0; i < size; i++){
		int index = IDArray[i];
		int pos;
		if(1){
			if(index==7){
				pos = getStatus(index) + decrPos +100;
			}else
				pos = getStatus(index) + decrPos;
		}else{
			pos = getStatus(index) - decrPos;
		}
		servoWrite(index, pos);
		setStatus(index, pos);
	}
	usleep(100000);
}

void changeDir(){
	int i;
	for(i=0;i<3;i++){
		MoveUp(hipB, 3, hips); 		//hips group B move up 100
		CMoveUp(axisA, 3, 300);	// axis group B move forward 60
		MoveDown(hipB, 3, hips);		//hips group B move down 100
		CMoveDown(axisA, 3, 300);	// axis group B move forward 60
		usleep(100000);
		MoveUp(hipA, 3, hips);		//hips group A move up 100
		CMoveUp(axisB, 3, 300);		// axis group A move backward 60
		MoveDown(hipA, 3, hips);		//hips group A move up 100
		CMoveDown(axisB, 3, 300);		// axis group A move backward 60
		usleep(100000);
	}
}
void LegMove(int hip[], int leg[], int index, int size, int hipd, int legd){
	int i = index;
	int hipidx = hip[i];
	int legidx = leg[i];
	int pos;
	if(isReversed[hipidx]){
		if(hipidx==7){
			pos = getStatus(hipidx) + hipd;// + 100;
		}else{
			pos = getStatus(hipidx) + hipd;
		}
	}else{
		pos = getStatus(hipidx) - hipd;
	}
	servoWrite(hipidx, pos);
	setStatus(hipidx, pos);
	usleep(100000);
	if(isReversed[legidx]){
		pos = getStatus(legidx) - legd;
	}else{
		pos = getStatus(legidx) + legd;
	}
	servoWrite(legidx, pos);
	setStatus(legidx, pos);
	usleep(100000);
}

void MoveAxisUp(int IDArray[], int size, int incrPos){
	int i;
	for(i = 0; i < size; i++){
		int index = IDArray[i];
		int pos;
		if(isReversed[index]){
				pos = getStatus(index) - incrPos;
		}else{
				pos = getStatus(index) + incrPos;
		}
		if(index == R1_1){ //Pull
			LegMove(hipB, legB, 0, 3, -t1, -t2); //Pull
		}else if(index == R3_1){
			LegMove(hipB, legB, 2, 3, -t3, -t4);   //Push
		}else if(index == L1_1){
			LegMove(hipA, legA, 0, 3, -t1, -t2); //Pull
		}else if(index == L3_1){
			LegMove(hipA, legA, 2, 3, -t3, -t4);   //Push
		}
		servoWrite(index, pos);
		setStatus(index, pos);
	}
}
void MoveUpHipsForReady(int hip[], int leg[], int size){
	LegMove(hip, leg, 0, size, -hips+t1, t2);	//Push
	LegMove(hip, leg, 1, size, -hips, 0);	//Push
	LegMove(hip, leg, 2, size, -hips+t3, t4);	//Push
}

void moveForward(){
	{// Ready for first step
		if(startmove == 0){
			MoveUpHipsForReady(hipB, legB, 3);
			startmove = 1;
		}
		MoveDown(axisB, 3, axis);				//axis group B move forward 60
		MoveDown(hipB, 3, hips);				//hips group B move down 100
	}
	{// Ready for second step
		MoveUpHipsForReady(hipA, legA, 3);
		// Move 1 step forward 
		MoveAxisUp(axisB, 3, axis);				//axis group B move backward 60
		MoveDown(axisA, 3, axis);				//axis group A move forward 60
	}
	{
		MoveDown(hipA, 3, hips);				//hips group A move down 100
		//MoveUp(hipB, 3, hips);					//hips group A move up 100
		MoveUpHipsForReady(hipB, legB, 3);
		// Move 2 step forward
		MoveAxisUp(axisA, 3, axis);				//axis group B move backward 60
	}
	{// End walking
		//if(startmove == 0){
		//	MoveDown(hipB, 3, hips);
		//}
	}
	printf("One Cycle\n");
}


void initializePosi(){
	int init;
	int i;
	printf("Do you want to reset position? : (0:no, 1:yes)");
	scanf("%d",&init);
	if(init == 1){
		for(i=0;i<19;i++){
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
			usleep(200000);
			servoWrite(i+2, position[i+2]+300);
			usleep(200000);
		}else{
			servoWrite(i+1, position[i+1]+500);
			usleep(200000);
			servoWrite(i+2, position[i+2]+300);
			usleep(200000);
		}
			servoWrite(i+2, position[i+2]);
			usleep(200000);
			servoWrite(i+1, position[i+1]);
			usleep(200000);
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
				pos = getStatus(index) - incrPos;// -100;
			}else
				pos = getStatus(index) - incrPos;
		}else{
				pos = getStatus(index) + incrPos;
		}
		servoWrite(index, pos);
		setStatus(index, pos);	
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
				pos = getStatus(index) + decrPos;// +100;
			}else
				pos = getStatus(index) + decrPos;
		}else{
			pos = getStatus(index) - decrPos;
		}
		servoWrite(index, pos);
		setStatus(index, pos);
	}
	usleep(100000);
}

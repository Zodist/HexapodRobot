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
int position2[19] = {
	1500, 1200, 1200,
	1000, 1350, 1400,
	900, 1100, 1400,
	1200, 1250, 1300,
	1800, 1000, 900,
	2200, 0 ,1200, 1000
	};
int position[19] = {
	1500, 1200, 1200,
	1000, 1350, 1400,
	900, 1100, 1400,
	1200, 1250, 1300,
	1800, 1000, 900,
	2200, 0 ,1200, 1000
	};
/*
int position[18] = {
	1500, 1000, 1000,
	1000, 1150, 1100,
	800, 900, 1200,
	1200, 1350, 1400,
	1800, 1100, 1000,
	2500, 1300, 1100
	};
*/
int isReversed[] = {
	1, 1, 0,
	1, 1, 0,
	1, 1, 0,
	0, 0, 1,
	0, 0, 1,
	0, 0, 0, 1
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

void downHips(int deg1, int deg2){
	int i;
	for(i=1;i<=7;i+=3){
		position[i] = position2[i]-deg1;
		servoWrite(i, position[i]);
		usleep(400000);

		position[i+1] = position2[i+1]+deg2;
		servoWrite(i+1, position[i+1]);
		usleep(400000);

	}
	for(i=10;i<=16;i+=3){
		position[i] = position2[i]+deg1;
		servoWrite(i, position[i]);
		usleep(400000);

		position[i+1] = position2[i+1]-deg2;
		servoWrite(i+1, position[i+1]);
		usleep(400000);
	}
}

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
		usleep(200000);
		MoveUp(hipA, 3, 500);		//hips group A move up 100
		CMoveUp(axisB, 3, 300);		// axis group A move backward 60
		MoveDown(hipA, 3, 500);		//hips group A move up 100
		CMoveDown(axisB, 3, 300);		// axis group A move backward 60
		usleep(100000);
	}
}

void LegPull(int hip[], int leg[], int size, int hipd, int legd){
	int i;
	for(i = 0; i < size; i+=2){
		int hipidx = hip[i];
		int legidx = leg[i];
		int pos;
		if(isReversed[hipidx]){
			pos = getStatus(hipidx) + hipd;
		}else{
			pos = getStatus(hipidx) - hipd;
		}
		servoWrite(hipidx, pos);
		setStatus(hipidx, pos);
		if(isReversed[legidx]){
			pos = getStatus(legidx) - legd;
		}else{
			pos = getStatus(legidx) + legd;
		}
		servoWrite(legidx, pos);
		setStatus(legidx, pos);
	}
	usleep(100000);
}
void LegMove(int hip[], int leg[], int index, int size, int hipd, int legd){
	int i = index;
	int hipidx = hip[i];
	int legidx = leg[i];
	int pos;
	if(isReversed[hipidx]){
		pos = getStatus(hipidx) + hipd;
	}else{
		pos = getStatus(hipidx) - hipd;
	}
	servoWrite(hipidx, pos);
	setStatus(hipidx, pos);
	usleep(200000);
	if(isReversed[legidx]){
		pos = getStatus(legidx) - legd;
	}else{
		pos = getStatus(legidx) + legd;
	}
	servoWrite(legidx, pos);
	setStatus(legidx, pos);
	usleep(200000);
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
		servoWrite(index, pos);
		if(index == R1_1){
			LegMove(hipB, legB, 0, 3, -200, -500); //Pull
		}else if(index == R3_1){
			LegMove(hipB, legB, 2, 3, 200, 500);   //Push
		}
		setStatus(index, pos);
	//	printf("servo : %d -> degree : %d\n", index, pos);
		
	}
	usleep(100000);
	//usleep(800000);
}
void MoveAxisDown(int IDArray[], int size, int decrPos){
	int i;
	for(i = 0; i < size; i++){
		int index = IDArray[i];
		int pos;
		if(isReversed[index]){
			pos = getStatus(index) + decrPos;
		}else{
			pos = getStatus(index) - decrPos;
		}
		servoWrite(index, pos);
		setStatus(index, pos);
		if(index == L1_1){
			LegMove(hipA, legA, 0, 3, -200, -500); //Pull
		}else if(index == L3_1){
			LegMove(hipA, legA, 2, 3, 200, 500);   //Push
		}
	//	printf("servo : %d -> degree : %d\n", index, pos);
	}
	usleep(100000);
	//usleep(800000);
}
int startmove = 0;
void moveForward(){
	/*
	MoveUp(hipB, 3, 600); 		//hips group B move up 100
	MoveDown(axisB, 3, 300);	// axis group B move forward 60
	MoveUp(axisA, 3, 300);		// axis group A move backward 60
	MoveDown(hipB, 3, 600);		//hips group B move down 100

	MoveUp(hipA, 3, 600);		//hips group A move up 100
	MoveUp(axisB, 3, 300);		// axis group B move backward 60
	MoveDown(axisA, 3, 300);	// axis group A move forward 60
	MoveDown(hipA,3, 600);		//hips group A move down 100
	
	usleep(200000);
	*/
	///*
	/*
	if(startmove == 0)
	{
		//Ready for first step
		MoveUp(hipB, 3, 500); 		//hips group B move up 100
		LegMove(hipB, legB, 0, 3, 200, 500); //Push
		MoveDown(axisB, 3, 300);	// axis group B move forward 60
		MoveDown(hipB, 3, 500);		//hips group B move down 100
		startmove = 1;
	}else{
		LegMove(hipA, legA, 2, 3, -200, -500);   //Push
		MoveUp(axisB, 3, 300);		// axis group A move forward 60
		MoveDown(hipB, 3, 500);		//hips group A move down 100
		
		MoveUp(hipB, 3, 500); 		//hips group B move up 100
		LegMove(hipB, legB, 0, 3, 200, 500); //Push
		MoveDown(axisB, 3, 300);	// axis group B move forward 60
		MoveDown(hipB, 3, 500);		//hips group B move down 100
		
		startmove = 1;
	}
	*/
	{// Ready for first step
		MoveUp(hipB, 3, 500); 		//hips group B move up 100
		LegMove(hipB, legB, 0, 3, 200, 500); //Push
		MoveDown(axisB, 3, 300);	// axis group B move forward 60
		MoveDown(hipB, 3, 500);		//hips group B move down 100
	}	
	{// Move 1 step forward
		MoveUp(hipA, 3, 500);		//hips group A move up 100
		MoveAxisUp(axisB, 3, 300);		// axis group B move backward 60
		//LegMove(hipB, legB, 0, 3, -200, -500); //Pull
		//LegMove(hipB, legB, 2, 3, 200, 500);   //Push
	}
	{// Ready for second step
		LegMove(hipA, legA, 0, 3, 200, 500);   //Push
		MoveUp(axisA, 3, 300);	// axis group A move forward 60
		MoveDown(hipA, 3, 500);		//hips group A move down 100
	}
	{// Move 2 step forward
		MoveUp(hipB, 3, 500);		//hips group A move up 100
		//LegMove(hipB, legB, 2, 3, -200, -500);   //Pull back
		MoveAxisDown(axisA, 3, 300);		// axis group B move backward 60
		//LegMove(hipA, legA, 0, 3, -200, -500); //Pull
		//LegMove(hipA, legA, 2, 3, 200, 500);   //Push
	}
	{// End walking
		LegMove(hipB, legB, 2, 3, -200, -500);   //Pull back
		MoveDown(hipB, 3, 500);
		MoveUp(hipA, 3, 500);
		LegMove(hipA, legA, 2, 3, -200, -500);   //Pull back
		MoveDown(hipA, 3, 500);
	}
	printf("One Cycle\n");
	usleep(200000);
	sleep(1);
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
	//usleep(800000);
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
	//usleep(800000);
}

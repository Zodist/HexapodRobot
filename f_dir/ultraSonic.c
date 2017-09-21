#include"SetMacro.h"
#include"RoboPiLib.h"
#define DETEC_DISTANCE	400
int detecForward(){
	int distance = 0x7fffffff;

	distance = readDistance(FORWARD);
	usleep(100000); // delay 0.1s
	
	//printf("Fdistance = %d\n",distance);
	if (distance < DETEC_DISTANCE) {
		printf("Object FORWARD\n");
		return 1;
	}
	return 0;
}
int detecLeft(){
	int distance = 0x7fffffff;

	distance = readDistance(LEFT);
	usleep(100000); // delay 0.1s
	
	//printf("Ldistance = %d\n",distance);
	if (distance < DETEC_DISTANCE) {
		printf("Object LEFT\n");
		return 1;
	}
	return 0;
}
int detecRight(){
	int distance = 0x7fffffff;

	distance = readDistance(RIGHT);
	usleep(100000); // delay 0.1s
	
	//printf("Rdistance = %d\n",distance);
	if (distance < DETEC_DISTANCE) {
		printf("Object RIGHT\n");
		return 1;
	}
	return 0;
}
/*
int detectObj() {
	int distance = 0x7fffffff;

	distance = readDistance(HC_SR);
	usleep(100000); // delay 0.1s
	
	//printf("**distance = %d\n",distance);
	if (distance < 300) {
	//	printf("**distance = %d\n",distance);
		return 1;
	}
			
	return 0;
}
*/
int detectObj() {
   int distance = 0x7fffffff;

   distance = readDistance(FORWARD);
   usleep(100000); // delay 0.1s
   printf("**forward : %d\n", distance);

   distance = readDistance(LEFT);
   usleep(100000); // delay 0.1s
   printf("**left : %d\n", distance);

   distance = readDistance(RIGHT);
   usleep(100000); // delay 0.1s
   printf("**right : %d\n", distance);
   /*   
   printf("**distance = %d\n",distance);
   if (distance < 300) {
   //   printf("**distance = %d\n",distance);
      return 1;
   }
   */   
   return 0;
}
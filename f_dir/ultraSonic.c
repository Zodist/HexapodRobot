#include"SetMacro.h"
#include"RoboPiLib.h"

int detectObj() {
	int distance = 0x7fffffff;

	distance = readDistance(HC_SR);
	usleep(100000); // delay 0.1s
	
	printf("**distance = %d\n",distance);
	if (distance < 300) {
	//	printf("**distance = %d\n",distance);
		return 1;
	}
			
	return 0;
}

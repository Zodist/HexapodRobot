//echo_server.c
#include <signal.h>
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include "Server.h"
extern int startflag; 
int nSockOpt = 1;

void serverInitialize() {
   serv_sock = socket(PF_INET, SOCK_STREAM, 0);
   if (serv_sock == -1)
      error_handling("socket() error");
   memset(&serv_addr, 0, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
   serv_addr.sin_port = htons(8000);
   setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &nSockOpt, sizeof(nSockOpt));
   if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)	 error_handling("bind() error");
}

void waitForClientConnect() {
   if (listen(serv_sock, 5) == -1) error_handling("listen() error");
   clnt_addr_size = sizeof(clnt_addr);
   clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
   if (clnt_sock == -1) error_handling("accept() error");
}

void sendXY() {
   while (1) {
      int x = rand();
      int j;
      printf("rand : %d\n", x);
      strcpy(message,"testMessage");
      write(clnt_sock, message, strlen(message));
   }
}
 
void error_handling(char *message)
{
	exit(1);
}

//Adding Thread Function
void *serverThreadF(void *data)
{
	WaitCameraInput();	
}

pid_t child_pid = 0;
void WaitCameraInput()
{
	pid_t pid;
	int ret;
	int readret;
	char buff[BUFSIZE];
	int fd;
	printf("WaitCameraInput Func Start(WaitForClientInput)\n");
	while ((str_len = read(clnt_sock, message, BUFSIZE)) != 0){
		printf("msg : %s\n", message);

		if (message[str_len - 2] == 'd') {
			startflag++;
			message[str_len - 2] = '\0';
			distance = atoi(message);
			printf("distance : %d\n", distance);
		}
		else if (message[str_len - 2] == 'r') {
			startflag++;
			direction = message[0];
			printf("direction : %c\n", direction);
		}
		else if(message[str_len-2]=='c'){
			pid=fork();
			switch(pid){	
				case -1: //error
					printf("fork failed\n");
					break;
				case 0: //child process	
					printf("Camera On\n");		
					ret = system("sh mjpg.sh");
					if (ret == 1) {
						printf("system failed");
						return;
					}
					break;
				default://parent process
					child_pid = 1;
					break;
			}
		}
		else if((message[str_len-2]=='q')){
			system("pgrep mjpg_streamer > mjpg.txt");
			if ((fd = open("./mjpg.txt", O_RDONLY)) > 0){
				read(fd, buff, BUFSIZE);
				printf("BUFFER : %s \n", buff);	

			}
			else{
				printf("Open failed.\n");
			}
			child_pid = atoi(buff);
			if (child_pid != 0) {
				kill(child_pid, SIGKILL);
				child_pid = 0;
			}
		}
		if(message != NULL)
			memset(message, '\0', sizeof(message));
	}
}
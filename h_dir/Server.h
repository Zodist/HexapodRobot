//#ifdef SERVER_HEADER
//#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
 
#define BUFSIZE 1024

int serv_sock;
int clnt_sock;
char message[BUFSIZE];
int str_len;
struct sockaddr_in serv_addr;
struct sockaddr_in clnt_addr;
int clnt_addr_size;
int distance = 0;
char direction = 0;
 
void serverInitialize();
void waitForClientConnect();
void waitForClientInput();
void sendXY();
void error_handling(char *message);
//#endif

//echo_server.c
#include "Server.h"
 
void serverInitialize() {
   serv_sock = socket(PF_INET, SOCK_STREAM, 0);
   if (serv_sock == -1)
      error_handling("socket() error");
   memset(&serv_addr, 0, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
   serv_addr.sin_port = htons(9000);
   if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)	 error_handling("bind() error");
}

void waitForClientConnect() {
   if (listen(serv_sock, 5) == -1) error_handling("listen() error");
   clnt_addr_size = sizeof(clnt_addr);
   clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
   if (clnt_sock == -1) error_handling("accept() error");
}

void waitForClientInput() {
    while ((str_len = read(clnt_sock, message, BUFSIZE)) != 0) {
        printf("msg : %s\n", message);
        if (message[str_len - 1] == 'd') {
            message[str_len - 1] = '\0';
            distance = atoi(message);
            printf("distance : %d\n", distance);
        }
        else if (message[str_len - 1] == 'r') {
            direction = message[0];
            printf("direction : %c\n", direction);
            if (distance != 0 && direction != '\0')
                break;
        }
        if(message != NULL)
            memset(message, '\0', sizeof(message));
    }
}

void sendXY() {
   while (1) {
      int x = rand();
      int j;
      printf("rand : %d\n", x);
 //     message[BUFSIZE] = "testMessage";
      strcpy(message,"testMessage");
      write(clnt_sock, message, strlen(message));
   }
}
 
void error_handling(char *message)
{
//   fputs(message, stderr);
//    fputc('\n', stderr);
//   exit(1);
}

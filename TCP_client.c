#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

#define PORT 15000

int main(){

  int clientSocket, ret;
  struct sockaddr_in serverAddr;
  char buffer[1024];

  clientSocket = socket(AF_INET, SOCK_STREAM, 0);  // For TCP we use SOCK_STREAM

  if(clientSocket < 0){
    printf("[-] Error in connection \n");
    exit(1);
  }

  printf("[+] Clent Socket is created \n");

  memset(&serverAddr, '\0', sizeof(serverAddr));

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(PORT);
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);  //inet_addr("127.0..0.1");

  ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

  if(ret < 0){
    printf("[-] Error in Connection \n");
  }
  printf("[+]Connected To server \n");

  

  FILE *fb=fopen("test.xml","r");
  
  int b;
  while( (b = fread(buffer, 1, sizeof(buffer), fb))>0 ){
        send(clientSocket, buffer, b, 0);
    }

    printf("\ndone");

  return 0;
}

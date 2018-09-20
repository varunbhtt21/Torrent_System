#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

#define PORT 15001


int main(){

	int sockfd, ret;
	struct sockaddr_in serverAddr;
  int newSocket;
  struct sockaddr_in newAddr;
  socklen_t addr_size;

	char buffer[1024];
	pid_t childpid;
     

  //
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if(sockfd < 0){
		printf("[-] Error in connection \n");
    	exit(1);
	}

	printf("[+] Clent Socket is created \n");





  memset(&serverAddr, '\0', sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(PORT);
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);                     //inet_addr("127.0..0.1");




  ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

  if(ret < 0){
  	printf("[-]Error in binding \n");
  	exit(1);
  }

  printf("[+]Bind to port %d\n", 4444);

  if(listen(sockfd, 10) == 0){
  	printf("[+]Listening.....\n");
  }
  else{
  	printf("[-]Error in binding \n");
  }






  int b = 0;

  while(1){


    //Socket Setup
    newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);

    if(newSocket < 0){
      exit(1);
    }
   
    printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));




    // File Writing Process
    FILE* fp = fopen( "test2.xml", "wb");
     
    if(fp != NULL){

        int total_bytes_send = 0;

        // Receiving Data and writing to file
        while( (b = recv(newSocket, buffer, 1024,0))> 0 ) {
                total_bytes_send += b;
                fwrite(buffer, 1, b, fp);
            }


         // Byte Size and Error Status
         printf("Received byte: %d\n",total_bytes_send);
           
            if (b<0){
               perror("Receiving");
             }

            fclose(fp);
  	  	}



     else {
         perror("File");
      }

      close(newSocket);
  				
  	}


  return 0;

}




#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <map>
#include <iterator>
#include <algorithm>
#include <fstream>
using namespace std; 

#define PORT 17044
#define PORT2 19031





int tracker_connection(char sync_data[5000]){


    struct sockaddr_in address; 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char hello[1000] = "Hello from client";

     
    char buffer[1024] = {0}; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    memset(&serv_addr, '0', sizeof(serv_addr)); 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT2); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    send(sock , sync_data , strlen(sync_data) , 0 ); 
    printf("Data sent to tracker2 and Ypur Data is\n"); 
  //  valread = read( sock , buffer, 1024); 
   // printf("%s\n",buffer ); 

    close(sock);
    return 0; 

}


























// Maintaining Seeder File
void copying_seeder_file() {
    
    std::ifstream in("temp_tracker_1.txt");
    std::ofstream out("seeder_list_1.txt", std::ios_base::out | std::ios_base::app);

    for (std::string str; std::getline(in, str); )
    {
        out << str;
    }
}
















int main()
{


	 // Variables for Sending Data
	 int sockfd, ret;
	 struct sockaddr_in serverAddr;
   int newSocket;
   struct sockaddr_in newAddr;
   socklen_t addr_size;

	 char buffer[4096];
   char sync_data[5000];
	 pid_t childpid;
     

         // Creating Socket
      	 sockfd = socket(AF_INET, SOCK_STREAM, 0);

      	 if(sockfd < 0){
      		  printf("[-] Error in connection \n");
          	exit(1);
      	  }

      	  printf("[+] Clent Socket is created \n");
  
      	memset(&serverAddr, '\0', sizeof(serverAddr));
      	serverAddr.sin_family = AF_INET;
      	serverAddr.sin_port = htons(PORT);
      	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);                     //inet_addr("127.0.0.1");



        // I.P and PORT binding
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








      int b = 0, flag=0;

      // Tracker keep on running
  		while(1)
      {
    	    	
                // Receiving data in buffer
                newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);    
        	    	
        	    	if(newSocket < 0){
        	      		exit(1);
        	    	} 
        	    	printf("Connection accepted from %s:%d valueof b %d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port),b);
    	         
                 

                // For Receiving data from client 
                if(b = recv(newSocket, buffer, 2048,0)> 0 ) {


                strcpy(sync_data, buffer);

                strcat(sync_data,"@hello");

                 
                //String Processing
                char* token;
                char key[5000], value[5000];

                

                // File Processing MULTIMAP
                FILE *seed;
                std::multimap<string, string> fetch;





                // Tokenizing String
                token = strtok(buffer, "$"); 
                strcpy(key, token);
       
                token = strtok(NULL, "$");  
                strcpy(value, token); 


    


             // Inserting an element in map
            fetch.insert(std::pair<string, string>(key, value));

            seed = fopen("temp_tracker_1.txt","w");

            // Running Iterator
            for (std::multimap<string, string>::iterator it = fetch.begin();
                it != fetch.end(); it++)
              fprintf(seed," %s  $  %s \n", it->first.c_str(), it->second.c_str());

            cout<<endl<<"Seeder File Updated"<<endl;
              
            fclose(seed);



          // For copying to Seeder File
            copying_seeder_file();
            cout<<"success";

           //close(newSocket);
           //close(sockfd);
           

           tracker_connection(sync_data);
           cout<<"\npehla socket bund ho gya or tracker nai data bhej dia";



        } // End of Tracker keep on running       
        	    
    close(newSocket);
        		
  }// End of Tracker code

    

	  return 0;
 }
  
   

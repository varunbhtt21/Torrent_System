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
#include<time.h>
using namespace std; 

#define PORT 18046
#define PORT2 19031





int synchronization(){


    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    char hello[1000] = "Hello from server"; 
       




    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 


    cout<<"\nTracker 2 : I am Listening \n";
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
   
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT2 ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 

    
    valread = read( new_socket , buffer, 1024); 
  //  printf("%s\n",buffer ); 

    cout<<"data received";
 //   send(new_socket , hello , strlen(hello) , 0 ); 
  //  printf("Hello message sent\n"); 

    char *token;
    char write_data1[1000], write_data2[1000];

    token = strtok(buffer, "@"); 
    strcpy(write_data1, token);
       
    token = strtok(NULL, "@");  
    strcpy(write_data2, token); 

   


    //file update


     char filename[ ] = "seeder_list_2.txt";

     fstream uidlFile(filename, std::fstream::in | std::fstream::out | std::fstream::app);


      if (uidlFile.is_open()) 
      {
        uidlFile << "\n";
        uidlFile << filename<<write_data1;
        uidlFile.close();
      } 
      else 
      {
        cout << "Cannot open file";
      }


    return 0; 


}
















void copying_seeder_file() {
    

    std::ifstream in("temp_tracker_2.txt");
    std::ofstream out("seeder_list_2.txt", std::ios_base::out | std::ios_base::app);

    for (std::string str; std::getline(in, str); )
    {
        out << str;
    }


}




int client_communication(){


  //cout<<jhanda; 
   int sockfd, ret;
   struct sockaddr_in serverAddr;
   int newSocket;
   struct sockaddr_in newAddr;
   socklen_t addr_size;

   char buffer[4096];
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
        serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);                     //inet_addr("127.0..0.1");



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

      //String Processing
      char* token;
      char key[5000], value[5000];

      // File Processing MULTIMAP
      FILE *seed;
      std::multimap<string, string> fetch;


      char sync_data[5000];

      // Tracker keep on running
      while(1)
      {
            
                // Receiving data in buffer
                newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);    
                
                if(newSocket < 0){
                    exit(1);
                } 
                printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
                
                if(b = recv(newSocket, buffer, 1024,0)> 0 ) {



                strcpy(sync_data, buffer);  


              // Tokenizing String
              token = strtok(buffer, "$"); 
              strcpy(key, token);
     
              token = strtok(NULL, "$");  
              strcpy(value, token); 






    


             // Inserting an element in map
            fetch.insert(std::pair<string, string>(key, value));

            seed = fopen("temp_tracker_2.txt","w");

            // Running Iterator
            for (std::multimap<string, string>::iterator it = fetch.begin();
                it != fetch.end(); it++)
              fprintf(seed," %s  $  %s \n", it->first.c_str(), it->second.c_str());

            cout<<endl<<"Seeder File Updated"<<endl;
              
            fclose(seed);





          // For copying to Seeder File
            copying_seeder_file();

            


           
           

        } // End of Tracker keep on running       
              
    close(newSocket);
            
  }// End of Tracker code

    



}










// Main code starts

int main()
{
  


 while(1){
            
            synchronization();


            
            client_communication();
          }


	  return 0;
 }
  
   





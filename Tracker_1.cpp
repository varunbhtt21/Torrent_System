

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
#include <sstream>
#include <string>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <pthread.h>
#include <stdlib.h> 
using namespace std; 

#define PORT 13095    // For Handling Client Request
#define PORT2 19036  // Tracker 1 to Tracker 2 For Synchronization
#define PORT3 25503 // Tracker 2 to Tracker 1 For Synchronization


std::multimap<string, string> fetch;



// Receiving Data From Tracker 1
void *synchronization_from_tracker2(void *threadid){


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


    
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
   
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT3 ); 
       
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


while(1){


  
              cout<<"\nTracker 1 : I am Listening \n";

              if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                                 (socklen_t*)&addrlen))<0) 
              { 
                  perror("accept"); 
                  exit(EXIT_FAILURE); 
              } 

              
              valread = read( new_socket , buffer, 1024); 
            //  printf("%s\n",buffer ); 

              cout<<"\n Tracker 1 Updated!!!\n";
           //   send(new_socket , hello , strlen(hello) , 0 ); 
            //  printf("Hello message sent\n"); 

             
              char write_data1[1000], write_data2[1000];
              strcpy(write_data2, buffer); 

             


              //file update


               char filename[ ] = "seeder_list_1.txt";

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
     }

  //  return 0; 


}




































// Sending Data To Tracker 2
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
    printf("Data sent to tracker2 !!!\n"); 
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
        out << "\n";
        out << str;
    }
}





void *client_handling(void *threadid){


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
              fprintf(seed," %s    %s ", it->first.c_str(), it->second.c_str());

            cout<<endl<<"Seeder File Updated"<<endl;
              
            fclose(seed);



          // For copying to Seeder File
            copying_seeder_file();
            cout<<"success";

           //close(newSocket);
           //close(sockfd);
           

           tracker_connection(sync_data);
           fetch.clear();
        } // End of Tracker keep on running       
              
      close(newSocket);
              
    }// End of Tracker code



}


/*

void *remove_key(){


std::ifstream infile("seeder_list_1.txt");

std::multimap<string, string> remove;

std::string line;


while (std::getline(infile, line))
{
    std::istringstream iss(line);
    int a, b;
    if (!(iss >> a >> b)) { break; } // error

    fetch.insert(std::pair<string, string>(a, b));
    // process pair (a,b)
}




}

*/













int main()
{

   

    pthread_t thread1, thread2;

    int  i=1;
    // make threads
    int sync = pthread_create(&thread1, NULL, synchronization_from_tracker2, NULL);

    int client = pthread_create(&thread2, NULL, client_handling, NULL);

  //  int remove = pthread_create(&thread2, NULL, client_handling, NULL);

  
    pthread_exit(NULL);
   
    

    return 0;
 }
  
   

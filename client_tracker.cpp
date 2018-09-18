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
using namespace std; 

#define PORT 15000

int main()
{
	
	int sockfd, ret;
	struct sockaddr_in serverAddr;
  	int newSocket;
  	struct sockaddr_in newAddr;
  	socklen_t addr_size;

	char buffer[4096];
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



  		int b = 0, flag=0;

  		while(1){

	    	newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);    
	    	
	    /*	if(newSocket < 0){
	      		exit(1);
	    	} */
	   
	    
	    	printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));


	         if(b = recv(newSocket, buffer, 1024,0)> 0 ) {
	                flag=1;
	            }

	          if(flag==1){
	          	break;
	          }   

	        }

		close(newSocket);

		


		//String Processing
		char* token;
		char key[5000], value[5000];

        token = strtok(buffer, "$"); 
  		strcpy(key, token);
	   
        token = strtok(NULL, "$");  
        strcpy(value, token);	






        // File Processing MULTIMAP
		FILE *seed;
		std::multimap<string, string> fetch;


	   // Inserting an element in map
		fetch.insert(std::pair<string, string>(key, value));


		seed = fopen("seeder_list.txt","w");
		for (std::multimap<string, string>::iterator it = fetch.begin();
				it != fetch.end(); it++)
			fprintf(seed," %s  $  %s \n", it->first.c_str(), it->second.c_str());
			
		fclose(seed);







	// File_Name ----------> Key
    
    char *next;
	next = strtok(value, "#");   
    strcpy(value, next);	
	

	std::map<std::string, string> track;
    track.insert(std::make_pair(value, key));

    FILE *keep_track;
    keep_track = fopen("Finding_key.txt","w");
    std::map<std::string, string>::iterator it = track.begin();


    while(it != track.end())
    {
        
        fprintf(keep_track," %s  $  %s \n", it->first.c_str(), it->second.c_str());
        fprintf(keep_track,"hello\n");
        it++;
    }
   

    fclose(keep_track);



	return 0;
}
  
   






  /*
   // Iterate over the multimap using Iterator
	for (std::multimap<string, string>::iterator it = fetch.begin();
			it != mmapOfPos.end(); it++)
		std::cout << it->first << " :: " << it->second << std::endl;

	





// Iterate over the multimap using range based for loop
	for (std::pair<char, int> elem : mmapOfPos)
		std::cout << elem.first << " :: " << elem.second << std::endl;       */




   /*
    std::map<std::string, int>::iterator it = mapOfWords.begin();
    while(it != mapOfWords.end())
    {
        std::cout<<it->first<<" :: "<<it->second<<std::endl;
        it++;
    }
    // Check if insertion is successful or not
    if(mapOfWords.insert(std::make_pair("earth", 1)).second == false)
    {
        std::cout<<"Element with key 'earth' not inserted because already existed"<<std::endl;
    }
    // Searching element in std::map by key.
    if(mapOfWords.find("sun") != mapOfWords.end())
        std::cout<<"word 'sun' found"<<std::endl;
    if(mapOfWords.find("mars") == mapOfWords.end())
        std::cout<<"word 'mars' not found"<<std::endl; */
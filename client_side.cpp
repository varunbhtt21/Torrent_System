#include <stdio.h>
#include <openssl/ssl.h>
#include <string.h>
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <fstream>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

#define PORT 13090  // For Tracker 1

#define PORT 13090  // For Tracker 2




int call_for_tracker1(char buffer[5000]){

  int clientSocket, ret, flag=0;
  struct sockaddr_in serverAddr;
  //char buffer[1024];

  clientSocket = socket(AF_INET, SOCK_STREAM, 0);  // For TCP we use SOCK_STREAM

  if(clientSocket < 0){
    printf("[-] Error in connection \n");
    flag = 1;
    exit(1);
  }

  printf("[+] Clent Socket is created \n");

  memset(&serverAddr, '\0', sizeof(serverAddr));

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(PORT);
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);  //inet_addr("127.0..0.1");

  ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

  if(ret < 0){
    flag=1;
    printf("[-] Error in Connection \n");
  }
  printf("[+]Connected To server \n");

  

  
  int b;

          b = send(clientSocket, buffer, b, 0);

          if(b==-1){

            flag=1;
        }

        else{
            printf("\ndone");
        }
      
    
    

    close(clientSocket);

  return flag;
  }













int call_for_tracker2(char buffer[5000]){

  int clientSocket, ret, flag=0;
  struct sockaddr_in serverAddr;
  //char buffer[1024];

  clientSocket = socket(AF_INET, SOCK_STREAM, 0);  // For TCP we use SOCK_STREAM

  if(clientSocket < 0){
    printf("[-] Error in connection \n");
    flag = 1;
    exit(1);
  }

  printf("[+] Clent Socket is created \n");

  memset(&serverAddr, '\0', sizeof(serverAddr));

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(PORT2);
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);  //inet_addr("127.0..0.1");

  ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

  if(ret < 0){
    flag=1;
    printf("[-] Error in Connection \n");
  }
  printf("[+]Connected To server \n");

  

  
  int b;

          b = send(clientSocket, buffer, b, 0);

          if(b==-1){

            flag=1;
        }

        else{
            printf("\ndone");
        }
      
    
    

    close(clientSocket);

  return flag;
  }
































// g++ client_side.cpp -L/usr/local/lib/ -lssl -lcrypto


// Calculate File Size
size_t size = 0;

void file_size(std::ofstream& myfile)
{                   
    static const char *SIZES[] = { "B", "kB", "MB", "GB" };
   
    size_t div = 0;
    size_t rem = 0;
    size_t result = 0; 

    while (size >= 1024 && div < (sizeof SIZES / sizeof *SIZES)) {
        rem = (size % 1024);
        div++;   
        size /= 1024;
    }

 //   fprintf(fb," %.1f %s ", (float)size + (float)rem / 1024.0, SIZES[div]);

    myfile << "Filesize : "<< (float)size + (float)rem / 1024.0 << SIZES[div] << "\n";


}





struct my_data
{


char file_name[100];
size_t file_size;
char file_path[500];
char ssh_key[999999];
};




int processing(char name[5000], char PATH[5000]){


FILE *ptr_readfile;
    char ch; /* or some other suitable maximum line size */
    int filecounter=1, charcounter=1, temp=0, data=0;  
    char buffer[999999];



    
    // FOR SHA-1
    unsigned char hash[SHA_DIGEST_LENGTH];
    unsigned char tmp[SHA_DIGEST_LENGTH]; 
    char buf[SHA_DIGEST_LENGTH*2];
    char pocket[999999];  
    

    ptr_readfile = fopen("test.txt","r");
    if (!ptr_readfile)
        return 1;



    int sha_pointer = 0 ;

    while (ch != EOF) {

        if (charcounter == 524288) {

            charcounter = 1;
            buffer[temp] = '\0';  // After Every String PUT NULL
            temp=0;  // Buffer Preparation for next iteration



            //Generate SSH key
            memset(buf, 0x0, SHA_DIGEST_LENGTH*2);
            memset(tmp, 0x0, SHA_DIGEST_LENGTH);
         
            SHA1((unsigned char *)buffer, strlen(buffer), tmp);
            int i;
            for (i=0; i < SHA_DIGEST_LENGTH; i++) {
                sprintf((char*)&(buf[i*2]), "%02x", tmp[i]);
            }


             //Fetching first 20 characters
           
            while(data<20){
                pocket[sha_pointer] = buf[data];
                data++;
                sha_pointer++;
            }

            
        }

            // putting data to buffer
            ch = fgetc(ptr_readfile);
            buffer[temp]=ch;

            // Maintaining buffer pointer and character count
            temp++;
            charcounter++;

            size++;

            data = 0 ; 
    }

            fclose(ptr_readfile);
       
            



            data = 0;

            // For remaining characters     
            if(charcounter != 1){

                buffer[temp] = '\0';


            //Generate SSH key
            memset(buf, 0x0, SHA_DIGEST_LENGTH*2);
            memset(tmp, 0x0, SHA_DIGEST_LENGTH);
         
            SHA1((unsigned char *)buffer, strlen(buffer), tmp);
            int i;
            for (i=0; i < SHA_DIGEST_LENGTH; i++) {
                sprintf((char*)&(buf[i*2]), "%02x", tmp[i]);
            }


             //Fetching first 20 characters
           
            while(data<20){
                pocket[sha_pointer] = buf[data];
                data++;
                sha_pointer++;
            }

     }

            pocket[sha_pointer] = '\0';


            // OUR SSH KEY IS READY in pocket variable
            
            



            // Variable Preparation For XML
           
            
            for(int i=0;i <strlen(name);i++)
            if(name[i]==' '){
                name[i]='_';
            }


            //Appending file name to PATH
            strcat(PATH, "/");
            strcat(PATH, name);




            
            
            
            struct my_data testData;
            strcpy(testData.file_name, name);
            testData.file_size = size;
            strcpy(testData.file_path, PATH);
            strcpy(testData.ssh_key, pocket);
            


            // String Preparation
            char string_processing[5000], num[5000], ip[500], port[500];

            strcat(string_processing, pocket);
            strcat(string_processing, "$");
            strcat(string_processing, testData.file_name);

            strcat(string_processing, "#");
            strcat(string_processing, ip);

            strcat(string_processing, "#"); 
            strcat(string_processing, port);


            strcat(name,".mtorrent");


            // mtorrent file created
            ofstream myfile;
            myfile.open (name);

            myfile << "Tracker1 URL1 : 127.0.0.1  13090 "<<"\n";
            myfile << "Tracker1 URL2 : 127.0.0.1  18050 "<<"\n";
            myfile << "Filename : "<< testData.file_name <<"\n";
       //     myfile << "Filesize : "<< testData.file_size << "\n";

            file_size(myfile);
            myfile << "Hash String : "<< pocket << "\n";
            

            myfile.close();

            cout<<"\n";

            cout<<testData.file_name<<".mtorrent File Generated!!!\n\n";



            int c = 0 , k = 0;
            c = call_for_tracker1(string_processing);

            if(c == 1){
                cout<<"Tracker1 is busy!!! Calling to Tracker 2";
               k = call_for_tracker2(string_processing);
            }

            if(k==1){
                cout<<"Both Trackers are busy";
            }

            exit(0);


}






int main() {
    
         string s1 = "share", s2 = "remove" , s3 = "get";
          char local_PATH[500], dest_PATH[500];
          char file_name[500];
          char ch;

    
            if( argc == 6 ) {
                  
               }



            while(1){
                printf("Press 1 : share\n");
                printf("Press 2 : remove\n");
                printf("Press 3 : get\n");
                printf("\n Please Enter The Choice : ");

                scanf("%c",&ch);

                    switch(ch){


                        case '1':  cout<<"Give File Name : ";
                                 cin>>file_name;
                                 cout<<"\n";

                                 cout<<"Give the Local PATH : ";
                                 cin>>local_PATH;
                                 cout<<"\n";

                                 cout<<"share "<<file_name<<" "<<local_PATH<<"\n";
                                 processing(file_name, local_PATH);
                                 cout<<"\n\n\n";
                                 break;

                        case '2':  
                                 cout<<"Give File Name : ";
                                 fgets(file_name, 100, stdin);
                                 cout<<"\n\n";

                                 cout<<"remove "<<file_name<<" "<<"\n";
                               //  remove_mtorrent(file_name);

                                 break;


                        default : cout<<"\nwrong choice\n";
                                   break;

                             }
                         }// End of while

            return 0;
}


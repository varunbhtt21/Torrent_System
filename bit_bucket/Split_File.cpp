#include <stdio.h>
#include <openssl/ssl.h>
#include <string.h>
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>

#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

#define PORT 15004



int call_for_tracker(char buffer[5000]){

  int clientSocket, ret;
  struct sockaddr_in serverAddr;
  //char buffer[1024];

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

  

  
  int b;

  send(clientSocket, buffer, b, 0);
      
    
    printf("\ndone");

    close(clientSocket);

  return 0;
}































// g++ Split_File.cpp -L/usr/local/lib/ -lssl -lcrypto


// Calculate File Size
size_t size = 0;

void file_size(FILE *fb)
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

    fprintf(fb," %.1f %s ", (float)size + (float)rem / 1024.0, SIZES[div]);


}




// XML CREATOR

struct my_data
{


char file_name[100];
size_t file_size;
char file_path[500];
char ssh_key[999999];
};


void createdata(FILE *fb, struct my_data testData)
{
fprintf ( fb,"<Data>\n");

fprintf ( fb,"<File_Name> %s </File_Name>\n",testData.file_name);

fprintf ( fb,"<File_Size>");
file_size(fb);
fprintf ( fb, "<File_Size>\n"); 

fprintf ( fb,"<File_Path> %s </File_Path>\n",testData.file_path);
fprintf ( fb,"<SSH_Key> %s </SSH_Key>\n",testData.ssh_key);

fprintf ( fb,"</Data>\n");

cout<<endl<<"FILE CREATED"<<endl;
}




// xml_creator(file_name, PATH, size, pocket);




int main() {
    
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





    while (ch != EOF) {

        if (charcounter == 524288) {

            charcounter = 1;
            buffer[temp] = '\0';  // After Every String PUT NULL


            //Generate SSH key
            memset(buf, 0x0, SHA_DIGEST_LENGTH*2);
            memset(tmp, 0x0, SHA_DIGEST_LENGTH);
         
            SHA1((unsigned char *)buffer, strlen(buffer), tmp);
            int i;
            for (i=0; i < SHA_DIGEST_LENGTH; i++) {
                sprintf((char*)&(buf[i*2]), "%02x", tmp[i]);
            }



            //Concatenate Strings
            strcat(pocket,buf);
            temp=0;
        }

            // Reading, putting, temp is buffer position and charcounter is counting characters
            ch = fgetc(ptr_readfile);
            buffer[temp]=ch;
            temp++;
            charcounter++;
            size++;
    }

            fclose(ptr_readfile);
       




            // OUR SSH KEY IS READY in pocket variable
            char name[100];
            char PATH[500];
            



            // Variable Preparation For XML
            cout<<"Enter File Name"<<endl;
            cin>>name;
            getcwd(PATH, sizeof(PATH));

            //Appending file name to PATH
            strcat(PATH, "/");
            strcat(PATH, name);




            
            // File Writing Started in XML Format 
            FILE *fb=fopen("test.xml","w");
            
            struct my_data testData;
            strcpy(testData.file_name, name);
            testData.file_size = size;
            strcpy(testData.file_path, PATH);
            strcpy(testData.ssh_key, pocket);
            


            // String Preparation
            char string_processing[5000], num[5000];

            strcat(string_processing, pocket);
            strcat(string_processing, "$");
            strcat(string_processing, testData.file_name);
            strcat(string_processing, "#");
            strcat(string_processing, testData.file_path);
            strcat(string_processing, "#");
            sprintf(num, "%zu", testData.file_size); 
            strcat(string_processing, num);


            call_for_tracker(string_processing);


            return 0;
}


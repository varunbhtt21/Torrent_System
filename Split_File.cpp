#include <stdio.h>
#include <openssl/ssl.h>
#include <string.h>
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
using namespace std;


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

fprintf ( fb,"<File_Name> %s </string>\n",testData.file_name);

fprintf ( fb,"<File_Size>");
file_size(fb);
fprintf ( fb, "<File_Size>"); 

fprintf (fb, "</number>\n");
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

            fprintf ( fb,"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
            createdata(fb, testData);

            return 0;
}


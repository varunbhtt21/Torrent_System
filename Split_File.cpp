#include <stdio.h>
#include <openssl/ssl.h>
#include <string.h>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;




int main() {
    FILE *ptr_readfile;
  //  FILE *ptr_writefile;
    char ch; /* or some other suitable maximum line size */
    int filecounter=1, charcounter=1, temp=0, data=0;
    
    char buffer[1000];
    unsigned char hash[SHA_DIGEST_LENGTH];


     unsigned char tmp[SHA_DIGEST_LENGTH]; 
     char buf[SHA_DIGEST_LENGTH*2];
     

     std::string key;
     char pocket[1000];
         
    

    ptr_readfile = fopen("test.txt","r");

    if (!ptr_readfile)
        return 1;


    while (ch != EOF) {

        if (charcounter == 512288) {
            charcounter = 1;
            filecounter++;
            data=0;
        }

        // fprintf(ptr_writefile,"%s\n", line);
         ch = fgetc(ptr_readfile);

         if(data<20){
            buffer[temp]=ch;
            temp++;
         }

         data++;


         if(data == 20){

             buffer[temp]='\0';

            memset(buf, 0x0, SHA_DIGEST_LENGTH*2);
            memset(tmp, 0x0, SHA_DIGEST_LENGTH);
         
            SHA1((unsigned char *)buffer, strlen(buffer), tmp);
            int i;
            for (i=0; i < SHA_DIGEST_LENGTH; i++) {
                sprintf((char*)&(buf[i*2]), "%02x", tmp[i]);
            }

            temp=0;
            strcat(pocket,buf);
         }


        charcounter++;
    }

     fclose(ptr_readfile);
   
    cout<<pocket;
    return 0;
}


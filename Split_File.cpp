#include <stdio.h>
#include <openssl/ssl.h>
#include <string.h>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

// g++ Split_File.cpp -L/usr/local/lib/ -lssl -lcrypto



int main() {
    FILE *ptr_readfile;
  //  FILE *ptr_writefile;
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
    }

            fclose(ptr_readfile);
       

            // OUR SSH KEY IS READY
            cout<<pocket;


            

            return 0;
}


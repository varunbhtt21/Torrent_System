#include<stdio.h>

struct my_data
{
int number;
char string[10];

char file_name[100];
int file_size;
char file_path[1000];
char ssh_key[100000];
};


void createdata(FILE *fb,struct my_data testData)
{

fprintf ( fb,"<Data>\n");

fprintf ( fb,"<File_Name> %s </string>\n",testData.file_name);
fprintf ( fb,"<File_Size> %d </number>\n",testData.file_size);
fprintf ( fb,"<File_Path> %s </string>\n",testData.file_path);
fprintf ( fb,"<SSH_Key> %s </string>\n",testData.ssh_key);

fprintf ( fb,"</Data>\n");
}



int main()
{
FILE *fb=fopen("test.xml","w");
struct my_data testData = {32,"Mr.32"};
fprintf ( fb,"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
createdata(fb,testData);
return 0;
}
#include<stdio.h>

struct my_data
{
int number;
char string[10];
};


void createdata(FILE *fb,struct my_data testData)
{
fprintf ( fb,"<Data>\n");
fprintf ( fb,"<number> %d </number>\n",testData.number);
fprintf ( fb,"<string> %s </string>\n",testData.string);
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
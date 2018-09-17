#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h>


int main() {
  struct stat file_status;
char *buf = NULL;
FILE * pFile;

stat("tmp.xml", &file_status);
buf = (char*)malloc(file_status.st_size);
pFile = fopen ("test.xml","r");
fread (buf,1,file_status.st_size,pFile);
printf("%s",buf);
fclose(pFile);
  return 0;
}
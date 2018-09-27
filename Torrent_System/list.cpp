#include "headers.h"


extern vector<string> file_name;
extern vector<string> file_perm;
extern vector<string> file_size;
extern vector<string> mod_date;
extern vector<string> gp_name;







int list(char PATH[100])
{

         char buf[100];  // for Modification time
         char PATH_temp[100];  // setting the file name printing problem
         string str1;
         char str[5]; // for storing rwx


         // Vector Clear
         file_name.clear();
         file_perm.clear();
         file_size.clear();
         mod_date.clear();
         gp_name.clear();


         // Directory Pointers
         DIR *dp = NULL;
         struct dirent *dptr = NULL;
         struct stat sbuf;
         struct group *grp_name;
         unsigned int count = 0;




         // PATH CHECKING
         if(PATH == NULL)
         {
             printf("\033[0;1;31m \033[2;150H ERROR : Could not get the working directory\n");
             return -1;
         }



         // CHECKING FILE OR DIRECTORY
         dp = opendir((const char*)PATH);
         if(dp==NULL)
         {
             printf("\033[0;1;31m \033[2;150H ERROR : Could not open the working directory\n");
             return -1;
         }


             // Accesing The Directory
             strcpy(PATH_temp,PATH);
             for(count = 0; NULL != (dptr = readdir(dp)); count++)
             {

                 // Temporary Path
                 strcat(PATH_temp,"/");
                 strcat(PATH_temp,dptr->d_name);

                 stat(PATH_temp,&sbuf);

                 file_name.push_back(dptr->d_name);


                // Set File Permission
                if(S_ISDIR(sbuf.st_mode)){
                       str[0]='d';
                     }
                else{  str[0]='-';  }

                 if(sbuf.st_mode & S_IREAD){
                        str[1]='r';
                      }
                  else{  str[1]='-';  }

                 if(sbuf.st_mode & S_IWRITE){
                        str[2]='w';
                      }
                 else{  str[2]='-';  }

                 if(sbuf.st_mode & S_IEXEC){
                        str[3]='x';
                      }
                  else{  str[3]='-';  }

                 file_perm.push_back(str);



                 // Set File Size
                 string size = to_string(sbuf.st_size);   // typecasting
                 file_size.push_back(size);


                 // Set Group Name
                 if ((grp_name = getgrgid(sbuf.st_gid)) != NULL)
                 {
                    gp_name.push_back(grp_name->gr_name);
                 }


                 // Set Modification Time
                 strcpy(buf,ctime(&sbuf.st_ctime));
                 mod_date.push_back(buf);

                 //Restoring the path
                 strcpy(PATH_temp,PATH);
             }

  return 0;
}










//  char *curr_dir = NULL;
 // char curr_dir[100];
//  DIR *dir; // for directory access

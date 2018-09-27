#include "headers.h"

extern vector<string> file_name;
extern vector<string> file_perm;
extern vector<string> file_size;
extern vector<string> mod_date;
extern vector<string> gp_name;



int store_vectors(char PATH[100],int cursor){


        int size = file_name.size();

        int count;

        printf("\033[6;H\n "); //Taking pointer to 8th row
        printf("\033[2;H\n\n \033[1;0;38m \033[11m------------------------------------------------------------------------*******Welcome To File-XP Explorer*******----------------------------------------------------------------------------------------\n\n\n");
        printf("\033[0;1;32m \t File Name  \t File Permission\tFile Size \t Modified Date \t \t \t   Group Name\n\n");
    //    printf("\033[?3l");
         printf("\n ");

        for(count=cursor;count<size;count++){

           cout<<"\033[10C"<<file_name[count]<<"\r";
           cout<<"\033[30C "<<file_perm[count]<<"\r";
           cout<<"\033[50C "<<file_size[count]<<"\r";
           cout<<"\033[100C "<<gp_name[count]<<"\r";
           cout<<"\033[60C"<<mod_date[count];

        }

        for(count=0;count<=cursor;count++)
        {
          cout<<"\033[10C"<<file_name[count]<<"\r";
          cout<<"\033[30C "<<file_perm[count]<<"\r";
          cout<<"\033[50C "<<file_size[count]<<"\r";
          cout<<"\033[100C "<<gp_name[count]<<"\r";
          cout<<"\033[60C"<<mod_date[count];
        }

        printf("\033[42;0H \033[0;1;38m ------------------------------------------------------------------------------------------COMMAND MODE SECTION------------------------------------------------------------------------------------------");

        printf("\033[4;180H \033[1;5;36m NORMAL MODE ");
      return 0;

      }

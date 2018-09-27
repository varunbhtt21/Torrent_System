#include "headers.h"

int process_command(char buffer[100], char fix_new[100])
{

    char arg1[100], arg2[100], item[100];
    string str;
    // Returns first token
    int len,i,j=0;
    queue <string> queue_string_process;

    len = strlen(buffer);



//***************************************************String Operation*********************************************************************
    i=0;
    j=0;
    // Breaking strings and inserting into queue
    buffer[len]=' ';
    while (i<=len)
    {
        if(buffer[i]==' ' || buffer[i]=='\0')
         {
            item[j]='\0';
            queue_string_process.push(item);
            item[j]=0;
            j=0;
            i++;
         }

         else
         {
            item[j]=buffer[i];
            i++;
            j++;

          }
    }



    // getting the command
    str = queue_string_process.front();
    strcpy(item,str.c_str());
    queue_string_process.pop();




//******************************COMMANDS HANDLED************************************************************************************



    // For Making Directory
    if(strncmp(item,"create_dir",10) == 0)
    {

      str=queue_string_process.front();
      strcpy(arg1,str.c_str()); // arg 1 is now ready i.e PATH
      queue_string_process.pop();

      str=queue_string_process.front();
      strcpy(arg2,str.c_str()); // arg 1 is now ready i.e PATH
      queue_string_process.pop();


      char temp[100];    // createdir filename filepath

            if(arg2[0]=='/')
            {
                strcpy(temp,arg2);
                strcat(temp,"/");
                strcat(temp,arg2);
                make_directory(temp);  //name and  path
            }

            else if(arg2[0]=='.')
            {
              strcpy(temp, fix_new);
              strcat(temp, "/");
              strcat(temp, arg1);
              make_directory(temp);
            }

            else
            {
              strcpy(temp,fix_new); // here we start to give address as  varun/work
              strcat(temp,"/");
              strcat(temp,arg2);
              strcat(temp,"/");
              strcat(temp,arg1);
              make_directory(temp);
            }

    }


//**************************************************************************************************************************************

    // For Creating File
    if(strncmp(item,"create_file",11) == 0)
    {

      str=queue_string_process.front();
      strcpy(arg1,str.c_str()); // file name
      queue_string_process.pop();

      str=queue_string_process.front();
      strcpy(arg2,str.c_str()); // path
      queue_string_process.pop();

      char temp[100];

      if(arg2[0]=='/')
      {
          strcpy(temp,arg2);
          strcat(temp,"/");
          strcat(temp,arg2);
          make_file(temp);  //name and  path
      }

      else if(arg2[0]=='.')
      {
        strcpy(temp, fix_new);
        strcat(temp, "/");
        strcat(temp, arg1);
        make_file(temp);
      }

      else
      {
        strcpy(temp,fix_new); // here we start to give address as  varun/work
        strcat(temp,"/");
        strcat(temp,arg2);
        strcat(temp,"/");
        strcat(temp,arg1);
        make_file(temp);
      }


    }


//***************************************************************************************************************************************

   // For Deleting Directory
    if(strncmp(item,"delete_dir",10) == 0)
    {
      printf("\e[2K]");
      str=queue_string_process.front();
      strcpy(arg1,str.c_str()); // arg 1 is now ready i.e PATH
      queue_string_process.pop();

      char temp[100];

      strcpy(temp,fix_new); // here we start to give address as  varun/work
      strcat(temp,"/");
      strcat(temp,arg1);

      remove_directory(temp);
       printf("\033[45;160H \033[0;1;31m Directory Removed !!!");
    }

//*******************************************************************************************************************************

// For snapshot
struct stat sbuf;

 if(strncmp(item,"snapshot",8) == 0)
 {
     printf("\e[2K]");
     str=queue_string_process.front();
     strcpy(arg1,str.c_str()); // arg 1 is now ready i.e PATH
     queue_string_process.pop();

     str=queue_string_process.front();
     strcpy(arg2,str.c_str()); // arg 2 is now ready i.e PATH
     queue_string_process.pop();




     char temp1[100];

       strcpy(temp1,fix_new);
       strcat(temp1,"/");
       strcat(temp1,arg1);

       snapshot(temp1, arg2);

      printf("\033[45;160H \033[31m Snapshot file created !!!");


 }




//*****************************************************************************************************************************************
//FOR SEARCHING



          if(strncmp(item,"search",6) == 0)
          {

              str=queue_string_process.front();
              strcpy(arg1,str.c_str()); // arg 1 is name of search file
              queue_string_process.pop();


              printf("\033[43;120H \033[1;0;29m SEARCH RESULTS");

              searching(fix_new, arg1);

          }


//************************************************Delete File**********************************************************************

          if(strncmp(item,"delete_file",11) == 0)
          {

              str=queue_string_process.front(); // delete_file PATH
              strcpy(arg1,str.c_str()); // arg 1 is PATH
              queue_string_process.pop();

              char temp[100];

              strcpy(temp,fix_new); // here we start to give address as  varun/work
              strcat(temp,"/");
              strcat(temp,arg1);

              delete_file(temp);

          }


//*********************************************GOTO*************************************************************************************

      if(strncmp(item,"goto",4) == 0)
      {

          str=queue_string_process.front(); // delete_file PATH
          strcpy(arg1,str.c_str()); // arg 1 is PATH
          queue_string_process.pop();

          char temp[100];

          if (arg1[0] == '/' && arg1[1]=='\0')
          {
              strcpy(temp,fix_new);
              goto_fn(temp);
          }

          else{
            goto_fn(arg1);
          }

      }




    return 0;
    }

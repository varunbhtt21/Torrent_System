#include "headers.h"



  int make_directory(char PATH[100])
  {
    //  mode_t mode = DEFAULT_MODE
   printf("\e[2K]");
   struct stat st;

    if (stat(PATH, &st) == -1) {
    mkdir(PATH, 0700);
    printf("\033[45;160H \033[0;1;31m Directory Created !!!");
    }

    else{
      printf("\033[45;160H \033[0;1;31m Directory Already Exists !!!");
    }

        return 0;

  }



//*************************************************GOTO**************************************************************************


            int goto_fn(char PATH[100])
            {
              //  mode_t mode = DEFAULT_MODE
               printf("\033[2J");
              list(PATH);
              store_vectors(PATH,0);
              return 0;
            }



//************************************************Creating File******************************************************************

  int make_file(char PATH[100])
  {
    //  mode_t mode = DEFAULT_MODE
       printf("\033[45;160H \e[2K]");

       int fd;
       fd=creat(PATH,S_IRWXU|S_IWUSR|S_IRGRP|S_IROTH);

       if(fd==1)
       {
       printf("\033[45;160H \033[0;1;31m File Created !!!");
       }

       else
       {
         printf("\033[45;160H \033[0;1;31m File Already Exists %d !!!",fd);
       }

    return 0;

  }

  //-------------------------------------------------Deletting File-----------------------------------------------------------------//



  //****************************************************Deleting File**************************************************************

  int delete_file(char PATH[100])
  {
    //  mode_t mode = DEFAULT_MODE

    struct stat del;

    if (!stat(PATH, &del))     // on success return 0
      {
              if(S_ISDIR(del.st_mode)){

                     printf("\033[45;160H \033[0;1;31m File Not Deleted !!!");
                  }

               else{
                      unlink(PATH);
                      printf("\033[45;160H \033[0;1;31m File Deleted !!!"); // on success return 0
                  }
      }

    return 0;

  }





int remove_directory(char PATH[100])
{

  DIR *dir = opendir(PATH);          // on sucess return pointer nd on failure eturn NULL
  struct dirent *read;
  char path_temp[100];
  struct stat sbuf;


  int val = 1;

  if(dir)
    {
      val=0;

          while(!val && (read=readdir(dir)) )  //returns a pointer to a dirent structure representing the next directory entry
          {

            int rem = 1;

              strcpy(path_temp, PATH);
              strcat(path_temp, "/");
              strcat(path_temp, read->d_name);

              if (!strcmp(read->d_name, ".") || !strcmp(read->d_name, "..")) //Important condition
              {
                 continue;
              }




              if (!stat(path_temp, &sbuf))     // on success return 0
                {

                        if(S_ISDIR(sbuf.st_mode)){
                               rem = remove_directory(path_temp);
                            }

                         else{
                               rem = unlink(path_temp);  // on success return 0
                            }
                }
                val = rem;

           }// END OF WHILE LOOP

          closedir(dir);
    }


       if(val == 0)
       {
         val = rmdir(PATH);       // On success return 0
       }


  return val;
}



//************************************************Snapshot*************************************************************************



    queue<string> snappy;
    FILE *fptr;
    int tag=0;
    int count=3;
    int snap_ptr=0;

    void snapshot(char PATH[100], char file[50])
    {

              DIR *dir = opendir(PATH);          // on sucess return pointer nd on failure eturn NULL
              struct dirent *read;
              char path_temp[100];
              struct stat sbuf;
              int flag=1;

              // Setting Header
              if(snap_ptr==0)
              {
                  string s;
                  fptr = fopen(file, "w");
                  fprintf(fptr,"*************************************************************************THIS IS YOUR SNAPSHOT FILE********************************************************************************************************\n\n");
                  fprintf(fptr,"\n\n\n\n");
              //    strcpy(s,file);
              //    fprintf(fptr, s.c_str());
                  fprintf(fptr,"  ->->  ");
                  snap_ptr=1;

                  fclose(fptr);

              }



                  if(dir)
                      {
                            flag=0;

                            while((read=readdir(dir)))  //returns a pointer to a dirent structure representing the next directory entry
                            {
                              fptr = fopen(file, "a+");
                              flag=1;

                                if (!strcmp(read->d_name, ".") || !strcmp(read->d_name, "..")) //Important condition
                                {
                                   continue;
                                }


                                //Setting the path
                                strcpy(path_temp, PATH);
                                strcat(path_temp, "/");
                                strcat(path_temp, read->d_name);


                                if (!stat(path_temp, &sbuf))     // on success return 0
                                  {

                                          if(S_ISDIR(sbuf.st_mode)){
                                                 snappy.push(path_temp);

                                                 fprintf(fptr,"%s    ", read->d_name); // Checking Directory
                                              }

                                           else{
                                                 fprintf(fptr,"%s    ", read->d_name);  // Checking File
                                              }
                                  }

                                  fclose(fptr);

                             }// END OF WHILE LOOP


                                 // Setting newline
                                 fptr = fopen(file, "a+");
                                 fprintf(fptr,"\t\t");
                                 string str;
                                 char temp[100];
                                 fprintf(fptr,"\n\n\n\n");
                                 fclose(fptr);



                             while (!snappy.empty())
                             {
                               fptr = fopen(file, "a+");

                               str = snappy.front();
                               strcpy(temp,str.c_str());
                               fprintf(fptr,"%s ->->-> ",temp);


                               snappy.pop();
                               fclose(fptr);
                               snapshot(temp, file);

                             }
                      }



                      if(flag==0)
                      {
                        string s1;
                        char temp[100];
                        fptr = fopen(file , "w");
                        s1="Directory is empty";
                        strcpy(temp,s1.c_str());
                        fprintf(fptr,"%s", temp);
                        fclose(fptr);
                      }

                      return;

    }




//*****************************************************Searching**********************************************************************



    int row = 45;

    void searching(char PATH[100], char search[50])
    {

              DIR *dir = opendir(PATH);          // on sucess return pointer nd on failure eturn NULL
              struct dirent *read;
              char path_temp[100];
              struct stat sbuf;


                  if(dir)
                      {

                            while((read=readdir(dir)))  //returns a pointer to a dirent structure representing the next directory entry
                            {

                                        if (!strcmp(read->d_name, ".") || !strcmp(read->d_name, "..") || !strcmp(read->d_name, ".git") ) //Important condition
                                        {
                                           continue;
                                        }


                                        //Setting the path
                                        strcpy(path_temp, PATH);
                                        strcat(path_temp, "/");
                                        strcat(path_temp, read->d_name);


                                        if (!stat(path_temp, &sbuf))     // on success return 0
                                          {

                                                  if(S_ISDIR(sbuf.st_mode))
                                                  {


                                                         if(strcmp(search,read->d_name)==0)
                                                         {
                                                           printf("\033[%d;120H \033[1;0;29m%s",row,path_temp);
                                                           row++;
                                                         }
                                                          searching(path_temp, search);
                                                  }


                                                   else
                                                     {

                                                        if(strcmp(search,read->d_name)==0)
                                                        {
                                                          printf("\033[%d;120H \033[1;0;29m %s",row,path_temp);
                                                          row++;
                                                          return;
                                                        }
                                                    }
                                          }


                             }// END OF WHILE LOOP

                      }
return;

    } // End of program






//*********************************************MOVE**********************************************************************************

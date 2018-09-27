# ifndef HEADERS_H
# define HEADERS_H

#include <iostream>

#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include<time.h>
#include<termios.h>
#include <string>
#include <grp.h>
#include <string.h>
#include <vector>
#include <queue>
#include <fcntl.h>
#include <algorithm>

using namespace std;


void current_wor_dir(char[]);
int list(char[]);
int make_directory(char[]);
int make_file(char[]);
int process_command(char[], char[]);
int store_vectors(char[],int);
void disableRawMode();
void enableRawMode();
int cursor_move();
int remove_directory(char[]);
void snapshot(char[], char[]);
void searching(char[], char[]);
int delete_file(char[]);
  int goto_fn(char[]);





#endif

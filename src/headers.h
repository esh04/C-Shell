#ifndef __HEADERS_H
#define __HEADERS_H

#include <stdio.h>    
#include <unistd.h>
#include <pwd.h>
#include <string.h>
#include <stdlib.h>
#include <error.h>
// #include <mach/error.h>
#include <errno.h>
#include <fcntl.h>
#include <ctype.h>
#include<stdbool.h>  
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>
#include <grp.h>
#include <time.h>
#include <sys/types.h>
#include <signal.h>

#include "signals.h"

#define MAX_SIZE 1000
#define MAX_LINE 300
#define MAX_HISTORY 20

// global variables

extern char *home; // home directory
extern char *prev_dir;
extern char **history;
extern char *history_path;
extern int shell_grpid;
extern processList process_list[MAX_LINE];
extern processList fg_process;
extern int bg_idx;
extern int time_taken_fg;
extern int storage_in, storage_out;

#endif
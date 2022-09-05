#ifndef __HEADERS_H
#define __HEADERS_H

#include <stdio.h>    
#include <unistd.h>
#include <pwd.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 1000
#define MAX_LINE 300
#define MAX_HISTORY 20

// global variables

extern char *home; // home directory
extern char *prev_dir;
extern char **history;
extern char *history_path;

#endif
#ifndef __HEADERS_H
#define __HEADERS_H

#include <stdio.h>    
#include <unistd.h>
#include <pwd.h>
#include <string.h>
#include <stdlib.h>
// #include <error.h>
#include <mach/error.h>
#include <errno.h>
#include <fcntl.h>
#include<stdbool.h>  

#define MAX_SIZE 1000
#define MAX_LINE 300

// global variables

extern char *home; // home directory
extern char *prev_dir;

#endif
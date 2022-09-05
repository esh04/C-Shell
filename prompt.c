#include "prompt.h"
#include "headers.h"

void prompt() {
    char hostname[HOST_NAME_MAX];
    char username[USER_NAME_MAX];

    // get username hostname
    gethostname(hostname, HOST_NAME_MAX);
    getlogin_r(username, USER_NAME_MAX);

    char *curr_path = getcwd(NULL,0); 

    char *disp_path; //path to be displayed

    char *substring = strstr(curr_path,home);

    // check if home is a substring of the current path 
    if(substring){
        disp_path = substring + strlen(home);
        // strcpy(disp_path,substring+strlen(home));
        printf("<%s@%s:~%s>", username, hostname, disp_path);
    }
    else
    {
        disp_path=curr_path;
        printf("<%s@%s:%s>", username, hostname, disp_path);
    }
    
}

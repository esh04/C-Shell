#include "prompt.h"
#include "headers.h"


void prompt() {
    char hostname[MAX_HOST_NAME];
    char username[MAX_USER_NAME];

    // get username hostname
    gethostname(hostname, MAX_HOST_NAME);
    getlogin_r(username, MAX_USER_NAME);

    char *curr_path = getcwd(NULL,0); 

    char *disp_path; //path to be displayed

    char *substring = strstr(curr_path,home);

    // check if home is a substring of the current path 
    if(substring){
        disp_path = substring + strlen(home);
        // strcpy(disp_path,substring+strlen(home));
        if(time_taken_fg >= 1)
        {
            printf("<%s@%s:~%s Took %ds>", username, hostname, disp_path, time_taken_fg);
            time_taken_fg = 0;
        }
        else
            printf("<%s@%s:~%s>", username, hostname, disp_path);
    }
    else
    {
        disp_path=curr_path;
        if(time_taken_fg >= 1)
            printf("<%s@%s:~%s Took %ds>", username, hostname, disp_path, time_taken_fg);
        else
            printf("<%s@%s:%s>", username, hostname, disp_path);
    }
    
}

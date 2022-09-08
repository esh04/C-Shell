#include "headers.h"
#include "cd.h"

void cd_cmd(int argc, char **arg_list){
    char *curr_dir = getcwd(NULL,0);

    if(argc==1){
        chdir(home);
    }
    else if(argc==2){
        if(strcmp(arg_list[1],"~")==0){
            chdir(home);
        }
        else if(strcmp(arg_list[1],"-")==0){
            if (prev_dir == NULL){
                // mimic shell behaviour
                printf("~\n");
                return;
            }
            chdir(prev_dir);
            printf("%s\n", prev_dir);
        }
        else {
            if(arg_list[1][0] == '~'){
                char *temp = arg_list[1] + 1;
                char *newpath = (char *)(malloc(MAX_SIZE* sizeof(char)));

                for(int i = 0; i < strlen(home); i++)
                    newpath[i] = home[i];
                }
                strcat(newpath,temp);
                chdir(newpath);
                free(newpath);
            }
            else
            {  
                chdir(arg_list[1]);
            }
        }
    }
    else {
        fprintf(stderr,"cd: Too many arguements\n");
        return;
    }
    prev_dir = curr_dir;
    return;
}

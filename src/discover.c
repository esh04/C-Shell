#include "headers.h"
#include "discover.h"
#include "ls.h"

void discover(char *target_dir, bool flag_d, bool flag_f, char *file){
    DIR *dir;

    bool f_files = false;
    bool f_dirs = false;

    if(flag_d == 0 && flag_f == 0){
        f_files = true;
        f_dirs = true;
    }
    else if(flag_d == 1 && flag_f == 0){
        f_dirs = true;
    }
    else if(flag_d == 0 && flag_f == 1){
        f_files = true;
    }
    else if(flag_d == 1 && flag_f == 1){
        f_files = true;
        f_dirs = true;
    }

    if(dir = opendir(target_dir)) {

        struct dirent *content;

        while((content = readdir(dir)) != NULL) {

            // ignoring hidden files
            if(content->d_name[0] == '.') {
                continue;
            } 

            // to include the hidden files, comment out code 33-34 and uncomment the below code
            // if(strcmp(content->d_name, ".") == 0 || strcmp(content->d_name, "..") == 0  ) {
                // continue;
            // } 


            if(file)
            {               
                if(strcmp(content->d_name, file) == 0) {
                    if((f_dirs == true  && content->d_type == DT_DIR) || (f_files == true && content->d_type == DT_REG)) {
                        printf("%s/%s\n", target_dir, content->d_name);
                    }   
                }
            }

            if(file == NULL) {
                if((f_dirs == true  && content->d_type == DT_DIR) || (f_files == true && content->d_type == DT_REG)) {
                    printf("%s/%s\n", target_dir, content->d_name);
                }
            }
       
            if(content->d_type == DT_DIR) {

                char *new_target_dir = (char*)malloc(sizeof(char) * MAX_SIZE);

                strcpy(new_target_dir, target_dir);

                if(target_dir[strlen(target_dir) - 1] != '/') 
                    strcat(new_target_dir, "/");

                strcat(new_target_dir, content->d_name);

                discover(new_target_dir, flag_d, flag_f, file);

                free(new_target_dir);
            }
        }

        if(closedir(dir) == -1) {
            perror("closedir");
        }

    }
    // else { 
    //     fprintf(stderr,"discover: No such file or directory\n");
    //     return;
    // }

    
}

void discover_cmd(int argc, char ** arg_list){

    bool flag_d = false, flag_f = false;
    bool dir_flag = false;
    bool file_flag = false;
    char *target_dir = ".";
    char *file = NULL;

    for(int i = 1; i<argc; i++){
        char *token = arg_list[i];

        if (token[0] == '-')
        {
            for (int i = 1; i < strlen(token); i++)
            {
                if (token[i] == 'd')
                {
                    flag_d = true;
                }
                else if (token[i] == 'f')
                {
                    flag_f = true;
                }
            }
        }
        else if(token[0] == '"'){
            if(file_flag == true)
            {
                fprintf(stderr, "discover: Multiple file names provided\n");
                return;
            }
            file = arg_list[i] + 1; // dont include first quote
            file[strlen(file)-1] = '\0'; // dont include last quote
            file_flag = true;

        }
        else
        {
            if(dir_flag == true)
            {
                fprintf(stderr, "discover: Multiple target directory names provided\n");
                return;
            }
            if (strcmp(token, "~") == 0)
            {
                strcpy(target_dir,home);
            }
            // replace ~ with home directory
            else if (token[0] == '~')
            {
                char *temp = (char*)malloc(sizeof(char) * MAX_SIZE);
                strcpy(temp, token);
                strcpy(token, home);
                strcat(token, temp+1);
                free(temp);

                strcpy(target_dir,token);

            }
            target_dir = arg_list[i];
            dir_flag = true;
        }
  
    }

    // if(file == NULL){
        // ls_cmd(2, (char *[]){"ls", target_dir});
    // }
    // else
    discover(target_dir, flag_d, flag_f, file);
    
    // printf("target_dir: %s\nflag_d: %d\nflag_f: %d\nfile: %s\n", target_dir, flag_d, flag_f, file);
    return;
}
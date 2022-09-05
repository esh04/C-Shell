#include "headers.h"
// void ls_a(char *dir){
//     printf("ls -a %s\n", dir);
//     return;
// }

// void ls(char *dir){
//     printf("ls %s\n", dir);
//     return;
// }

// void ls_l(char *dir, bool flag_a){
//     if(flag_a == true){
//         printf("ls -al %s\n", dir);
//     }
//     else if(flag_a == false){
//         printf("ls -l %s\n", dir);
//     }
//     return;
// }

void ls_cmd(int argc, char **arg_list){

    bool flag_l = false;
    bool flag_a = false;
    int num = 0;

    char pathsArray[MAX_SIZE][MAX_SIZE];
    char *curPath = getcwd(NULL,0);


    strcpy(pathsArray[0], curPath);

    for(int i = 1; i<argc; i++){
        char *token = arg_list[i];

        if (token[0] == '-')
        {
            for (int i = 1; i < strlen(token); i++)
            {
                if (token[i] == 'l')
                {
                    flag_l = true;
                }
                else if (token[i] == 'a')
                {
                    flag_a = true;
                }
            }
        }
        else if (strcmp(token, "~") == 0)
        {
            strcpy(pathsArray[num],home);
            num++;
        }
        else
        {
            strcpy(pathsArray[num], token);
            num++;
        }
    }

    printf("PATHS:\n");
    for(int i = 0; i < num; i++)
    {
        printf("%s\n",pathsArray[i]);
    }
    printf("A:%d\n",flag_a);
    printf("L:%d\n",flag_l);
    printf("patharray[0]: %s\n",pathsArray[0]);

    return;
}


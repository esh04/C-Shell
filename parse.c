#include "headers.h"
#include "parse.h"
#include "echo.h"
#include "pwd.h"
#include "cd.h"

void parse(char *input){
    char *string = malloc(1000*(sizeof(char))), *token, *subtoken, *ptr1, *ptr2;
    strcpy(string, input);
    token = strtok_r(string, ";\n", &ptr1);

    while(token!=NULL)
    {
        char **commands = (char**)(malloc(100*(sizeof(char*))));
        subtoken = strtok_r(token," \t\r\n\a", &ptr2);
        int argc = 0;
        while (subtoken!=NULL)
        {
            commands[argc++] = subtoken;
            subtoken = strtok_r(NULL," \t\r\n\a", &ptr2);
        }
        // execute command here
        if (strcmp(commands[0],"echo")==0) 
            echo_cmd(argc,commands);
        else if (strcmp(commands[0],"pwd")==0) 
            pwd_cmd();
        else if (strcmp(commands[0],"cd")==0) 
            cd_cmd(argc,commands);
        else if (strcmp(commands[0], "exit") == 0)
            exit(0);
        token = strtok_r(NULL,";\n",&ptr1);
    }
    free(string);
    return;
}


#include "headers.h"
#include "parse.h"
#include "echo.h"
#include "pwd.h"
#include "cd.h"
#include "pinfo.h"
#include "ls.h"
#include "history.h"
#include "execvp.h"
#include "discover.h"

void execute( char *commands[], int argc){

    // execute command here
    if (strcmp(commands[0],"echo")==0) 
        echo_cmd(argc,commands);
    else if (strcmp(commands[0],"pwd")==0) 
        pwd_cmd();
    else if (strcmp(commands[0],"cd")==0) 
        cd_cmd(argc,commands);
    else if (strcmp(commands[0],"pinfo")==0) 
        pinfo_cmd(argc, commands);
    else if (strcmp(commands[0], "ls") == 0)
        ls_cmd(argc, commands);
    else if (strcmp(commands[0], "history") == 0)
        history_cmd(argc, commands);
    else if(strcmp(commands[0], "discover") == 0)
        discover_cmd(argc, commands);
    else if (strcmp(commands[0], "exit") == 0)
        exit(0);
    else
        execvp_cmd(argc,commands);
}


void parse(char *input){
    
    char *string = malloc(MAX_SIZE*(sizeof(char))), *token, *subtoken, *ptr1, *ptr2;
    
    strcpy(string, input);

    // add ' ; ' after every '&'
    for(int i = 0; i<strlen(string); i++)
    {
        if(string[i] == '&')
        {
            if(string[i+1] != ';')
            {
                char *temp = malloc(MAX_SIZE*(sizeof(char)));
                strcpy(temp, string + i + 1);
                string[i+1] = ';';
                strcpy(string + i + 2, temp);
                free(temp);
            }
            else
                fprintf(stderr, "Invalid syntax\n");
        }
    } 

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
       
        execute(commands, argc);

        token = strtok_r(NULL,";\n",&ptr1);
        free(commands);
    }
    free(string);
    return;
}

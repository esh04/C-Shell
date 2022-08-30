#include "headers.h"
#include "parse.h"
#include "echo.h"


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
            echo_cmd(commands);
        // else if (strcmp(arg_list[0],"pwd")) 
        //     pwd_cmd();
        // else if (strcmp(arg_list[0],"cd")) 
        //     cd_cmd();
 


        token = strtok_r(NULL,";\n",&ptr1);
    }
    return;
}


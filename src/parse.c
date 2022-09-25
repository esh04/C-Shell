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
#include "redirect.h"
#include "sig.h"
#include "job.h"
#include "bg.h"
#include "fg.h"

void execute(char *commands[], int argc)
{
    // execute command here
    if (strcmp(commands[0], "echo") == 0)
        echo_cmd(argc, commands);
    else if (strcmp(commands[0], "pwd") == 0)
        pwd_cmd();
    else if (strcmp(commands[0], "cd") == 0)
        cd_cmd(argc, commands);
    else if (strcmp(commands[0], "pinfo") == 0)
        pinfo_cmd(argc, commands);
    else if (strcmp(commands[0], "ls") == 0)
        ls_cmd(argc, commands);
    else if (strcmp(commands[0], "history") == 0)
        history_cmd(argc, commands);
    else if (strcmp(commands[0], "discover") == 0)
        discover_cmd(argc, commands);
    else if (strcmp(commands[0], "sig") == 0)
        sig_cmd(argc, commands);
    else if (strcmp(commands[0], "jobs") == 0)
        job_cmd(argc, commands);
    else if (strcmp(commands[0], "bg") == 0)
        bg_cmd(argc, commands);
    else if (strcmp(commands[0], "fg") == 0)
        fg_cmd(argc, commands);
    else if (strcmp(commands[0], "exit") == 0)
        exit(0);
    else
        execvp_cmd(argc, commands);

    return;
}


void redirect(char *commands[], int argc)
{
    // declare a new command array
    char **new_command = malloc(MAX_LINE * sizeof(char *));
    int new_argc = 0;

    storage_in = dup(0);
    storage_out = dup(1);

    // parse for redirection
    for (int i = 0; i < argc; i++)
    {
        char *inputfile = NULL;
        char *outputfile = NULL;

        if (strcmp(commands[i], "<") == 0)
        {
            inputfile = commands[i + 1];
            i += 1; // no need to parse the filename (don't include in final command)
            if (input_redirect(inputfile) == -1)
            {
                fprintf(stderr, "Error in input redirection\n");
                return;
            }
        }
        else if (strcmp(commands[i], ">") == 0)
        {
            outputfile = commands[i + 1];
            i += 1;
            if (output_redirect(outputfile) == -1)
            {
                fprintf(stderr, "Error in output redirection\n");
                return;
            }
        }
        else if (strcmp(commands[i], ">>") == 0)
        {
            outputfile = commands[i + 1];
            i += 1;
            if (append_redirect(outputfile) == -1)
            {
                fprintf(stderr, "Error in append redirection\n");
                return;
            }
        }
        else
        {
            new_command[new_argc] = commands[i];
            new_argc += 1;
        }
    }

    execute(new_command, new_argc);
    restore_dup();

    free(new_command);
}

void parse_token(char *input){
    char *string = malloc(MAX_SIZE * (sizeof(char))), *subtoken,*ptr2;

    strcpy(string, input);

    char **commands = (char **)(malloc(MAX_LINE * (sizeof(char *))));
    subtoken = strtok_r(string, " \t\r\n\a", &ptr2);
    int argc = 0;
    while (subtoken != NULL)
    {
        commands[argc++] = subtoken;
        subtoken = strtok_r(NULL, " \t\r\n\a", &ptr2);
    }

    redirect(commands, argc);

    free(commands);
    free(string);    
}


void parse_pipes(char *input){
    char *string = malloc(MAX_SIZE * (sizeof(char))), *subtoken,*ptr2;

    strcpy(string, input);

    char **commands = (char **)(malloc(MAX_LINE * (sizeof(char *))));
    subtoken = strtok_r(string, "|", &ptr2);
    int argc = 0;
    while (subtoken != NULL)
    {
        commands[argc++] = subtoken;
        subtoken = strtok_r(NULL, "|", &ptr2);
    }

    if(argc == 1){
        parse_token(commands[0]);
    }
    else {
        // add pipes code here
        for(int i=0;i<argc;i++){
            parse_token(commands[i]);
        }
    }

    free(commands);
    free(string);       
}

void parse(char *input)
{

    char *string = malloc(MAX_SIZE * (sizeof(char))), *token, *ptr1;

    strcpy(string, input);

    // add ' ; ' after every '&'
    for (int i = 0; i < strlen(string); i++)
    {
        if (string[i] == '&')
        {
            if (string[i + 1] != ';')
            {
                char *temp = malloc(MAX_SIZE * (sizeof(char)));
                strcpy(temp, string + i + 1);
                string[i + 1] = ';';
                strcpy(string + i + 2, temp);
                free(temp);
            }
            else
                fprintf(stderr, "Invalid syntax\n");
        }
    }

    token = strtok_r(string, ";\n", &ptr1);

    while (token != NULL)
    {
        parse_pipes(token);
        // printf("%s\n", token);
        token = strtok_r(NULL, ";\n", &ptr1);
    }
    free(string);
    return;
}



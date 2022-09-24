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

void execute(char *commands[], int argc)
{
    // declare a new command array
    char **new_command = malloc(MAX_LINE * sizeof(char *));
    int new_argc = 0;

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

    // execute command here
    if (strcmp(new_command[0], "echo") == 0)
        echo_cmd(new_argc, new_command);
    else if (strcmp(new_command[0], "pwd") == 0)
        pwd_cmd();
    else if (strcmp(new_command[0], "cd") == 0)
        cd_cmd(new_argc, new_command);
    else if (strcmp(new_command[0], "pinfo") == 0)
        pinfo_cmd(new_argc, new_command);
    else if (strcmp(new_command[0], "ls") == 0)
        ls_cmd(new_argc, new_command);
    else if (strcmp(new_command[0], "history") == 0)
        history_cmd(new_argc, new_command);
    else if (strcmp(new_command[0], "discover") == 0)
        discover_cmd(new_argc, new_command);
    else if (strcmp(new_command[0], "exit") == 0)
        exit(0);
    else
        execvp_cmd(new_argc, new_command);

    restore_dup();
    free(new_command);
}

void parse(char *input)
{

    char *string = malloc(MAX_SIZE * (sizeof(char))), *token, *subtoken, *ptr1, *ptr2;

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
        char **commands = (char **)(malloc(MAX_LINE * (sizeof(char *))));
        subtoken = strtok_r(token, " \t\r\n\a", &ptr2);
        int argc = 0;
        while (subtoken != NULL)
        {
            commands[argc++] = subtoken;
            subtoken = strtok_r(NULL, " \t\r\n\a", &ptr2);
        }

        execute(commands, argc);

        token = strtok_r(NULL, ";\n", &ptr1);
        free(commands);
    }
    free(string);
    return;
}

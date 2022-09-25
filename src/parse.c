#include "headers.h"
#include "parse.h"
#include "redirect.h"

void parse_token(char *input)
{
    char *string = malloc(MAX_SIZE * (sizeof(char))), *subtoken, *ptr2;

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

int parse_pipes(char *input)
{
    char *string = malloc(MAX_SIZE * (sizeof(char))), *subtoken, *ptr2;

    strcpy(string, input);

    char **commands = (char **)(malloc(MAX_LINE * (sizeof(char *))));
    subtoken = strtok_r(string, "|", &ptr2);
    int argc = 0;
    while (subtoken != NULL)
    {
        commands[argc++] = subtoken;
        subtoken = strtok_r(NULL, "|", &ptr2);
    }

    if (argc == 1)
    {
        parse_token(commands[0]);
    }
    else
    {
        commands[argc] = NULL;
        int fd[2];
        int fd_in = STDIN_FILENO;

        for (int i = 0; i < argc; ++i)
        {

            if (pipe(fd) == -1)
            {
                perror("pipe");
                return -1;
            }

            pid_t forkReturn = fork();
            if (forkReturn == -1)
            {
                perror("fork");
                return -1;
            }
            else if (forkReturn == 0)
            {
                if (i > 0)
                    dup2(fd_in, STDIN_FILENO);
                if (i < argc - 1)
                {
                    dup2(fd[1], STDOUT_FILENO);
                }
                if(close(fd[0]) == -1)
                {
                    perror("close");
                    return -1;
                }
                parse_token(commands[i]);
                exit(0);
            }
            else
            {
                wait(NULL);
                if(close(fd[1]) == -1)
                {
                    perror("close");
                    return -1;
                }
                fd_in = fd[0];
            }
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

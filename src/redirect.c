#include "headers.h"
#include "execute.h"

int input_redirect(char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        fprintf(stderr, "< : Error opening file");
        return -1;
    }
    dup2(fd, STDIN_FILENO); // redirect stdin to file
    if (close(fd))
    {
        fprintf(stderr, "< : Error closing file");
        return -1;
    }
    return 0;
}

int output_redirect(char *filename)
{
    // check if filename is not empty
    if (filename == NULL)
    {
        fprintf(stderr, "> : No filename specified");
        return -1;
    }

    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd == -1)
    {
        fprintf(stderr, "> : Error opening file");
        return -1;
    }

    dup2(fd, STDOUT_FILENO); // redirect stdout to file

    if (close(fd))
    {
        fprintf(stderr, "> : Error closing file");
        return -1;
    }
    return 0;
}

int append_redirect(char *filename)
{
    int fd = open(filename, O_WRONLY | O_APPEND, 0644);
    if (fd == -1)
    {
        fprintf(stderr, ">> : Error opening file");
        return -1;
    }
    dup2(fd, STDOUT_FILENO); // redirect stdout to file
    if (close(fd))
    {
        fprintf(stderr, ">> : Error closing file");
        return -1;
    }
}

void restore_dup()
{
    dup2(storage_out, STDOUT_FILENO);
    dup2(storage_in, STDIN_FILENO);
    return;
}

void redirect(char *commands[], int argc)
{
    // declare a new command array
    char **new_command = malloc(MAX_LINE * sizeof(char *));
    int new_argc = 0;

    int storage_in = dup(STDIN_FILENO);
    int storage_out = dup(STDOUT_FILENO);

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

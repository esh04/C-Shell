#include "headers.h"


int input_redirect(char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        fprintf(stderr, "< : Error opening file");
        return -1;
    }
    dup2(fd, STDIN_FILENO); //redirect stdin to file
    if(close(fd)){
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
    
    dup2(fd, STDOUT_FILENO); //redirect stdout to file

    if(close(fd)){
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
    dup2(fd, STDOUT_FILENO); //redirect stdout to file
    if(close(fd)){
        fprintf(stderr, ">> : Error closing file");
        return -1;
    }
}

void restore_dup(){
    dup2(storage_out, STDOUT_FILENO);
    dup2(storage_in, STDIN_FILENO);
    return;
}
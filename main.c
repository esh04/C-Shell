#include "headers.h"
#include "prompt.h"
#include "parse.h"

char *home;
char *prev_dir;
char **history;
char *history_path;

void main()
{
    // store home directory
    home = getcwd(NULL,0);
    history_path = malloc(MAX_SIZE*sizeof (char));
    sprintf(history_path,"%s/history.txt",getcwd(NULL,0));
    prev_dir = NULL;
    history = calloc(MAX_HISTORY,sizeof(char *));

    while (1)
    {
        prompt();
        char *line = NULL;
        size_t sz = MAX_SIZE;

        ssize_t flag1 = getline(&line,&sz,stdin);

        parse(line);
    }

    return;
}

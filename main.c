#include "headers.h"
#include "prompt.h"
#include "parse.h"
#include "history.h"

char *home;
char *prev_dir;
char **history;
char *history_path;

int main()
{
    // store home directory
    home = getcwd(NULL,0);
    prev_dir = NULL;

    // history_path = malloc(MAX_SIZE*sizeof (char)); 
    // sprintf(history_path,"%s/history.txt",getcwd(NULL,0));
    history_path ="./history.txt";

    history = malloc(MAX_HISTORY*sizeof(char *));
    load_history();

    while (1)
    {
        prompt();
        char *line = NULL;
        size_t sz = MAX_SIZE;

        ssize_t flag1 = getline(&line,&sz,stdin);

        store_history(line);
        parse(line);

    }
    free(history);
    free(history_path);
    return 0;
}

#include "headers.h"
#include "prompt.h"
#include "parse.h"
#include "history.h"
#include "finishbg.h"

char *home;
char *prev_dir;
char **history;
char *history_path;
int shell_grpid;
processList process_list[MAX_LINE];
int bg_idx;
int time_taken_fg;

int main()
{
    // store home directory
    home = getcwd(NULL,0);
    prev_dir = NULL;

    time_taken_fg = 0;

    history_path = malloc(MAX_SIZE*sizeof (char)); 
    sprintf(history_path,"%s/history.txt",home);
    // history_path ="./history.txt";

    history = malloc(MAX_HISTORY*sizeof(char *));
    load_history();

    init_process_list();
    shell_grpid = getpgid(getpid());
    signal(SIGCHLD,finish_bg);

    while (1)
    {
        prompt();
        char *line = NULL;
        size_t sz = MAX_SIZE;

        getline(&line,&sz,stdin);

        store_history(line);
        parse(line);

    }
    free(history);
    free(history_path);
    return 0;
}

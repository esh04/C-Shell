#include "headers.h"
#include "signals.h"

int fg_cmd(int argc, char **arg_list)
{
    if (argc != 2)
    {
        fprintf(stderr, "fg: incorrect number of arguments\n");
        return -1;
    }

    int num = atoi(arg_list[1]) - 1;
    if (num < 0 || num > bg_idx)
    {
        fprintf(stderr, "fg: invalid job number\n");
        return -1;
    }
    int process_pid = process_list[num].pid;

    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    if (tcsetpgrp(STDIN_FILENO, process_pid) == -1)
    {
        fprintf(stderr, "fg: Error\n");
        return -1;
    }
    else
    {
        int status;
        if (kill(process_pid, SIGCONT) != 0)
        {
            fprintf(stderr, "fg: Error\n");
            return -1;
        }
        remove_process(process_pid);     // remove process from process_list (bg process)

        fg_process.pid = process_pid;
        fg_process.process_name = process_list[num].process_name;
        waitpid(-1, &status, WUNTRACED); 
        fg_process.pid = -1;
        fg_process.process_name = NULL;
        
        if (WIFSTOPPED(status))
        {
            add_process(process_pid, process_list[num].process_name);
        }
        tcsetpgrp(STDIN_FILENO, getpgrp());
        signal(SIGTTIN, SIG_DFL);
        signal(SIGTTOU, SIG_DFL);
    }

    return 0;
}

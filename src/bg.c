#include "headers.h"

int bg_cmd(int argc, char **arg_list){
    if(argc != 2){
        fprintf(stderr, "bg: incorrect number of arguments\n");
        return -1;
    }

    int num = atoi(arg_list[1]) - 1;
    if(num<0 || num>bg_idx)
    {
        fprintf(stderr, "bg: invalid job number\n");
        return -1;
    }
    int process_pid = process_list[num].pid;

    if(kill(process_pid,SIGCONT) != 0){
        fprintf(stderr, "bg: Error\n");
        return -1;
    }

    return 0;
}

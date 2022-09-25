#include "headers.h"

// check working
int sig_cmd(int argc, char **arg_list){
    if(argc == 3){
        int sig = atoi(arg_list[2]);
        int num = atoi(arg_list[1]);
        if(num<0 || num>bg_idx){
            fprintf(stderr, "sig: No such process\n");
            return -1;
        }
        kill(process_list[num-1].pid,sig);
        return 0;
    }
    else{
        fprintf(stderr, "sig: incorrect number of arguments\n");
        return -1;
    }
}

#include "headers.h"
#include "signal.h"


void init_process_list(){
    for(int x=0;x<MAX_LINE;x++)
        process_list[x].process_name = NULL, process_list->pid = 0;
}


char * get_process_name(int pid){
    for(int x=0;x<MAX_LINE;x++)
        if(process_list[x].pid == pid)
            return process_list[x].process_name;
    return NULL;
}

int remove_process(int pid){
    for(int x=0;x<MAX_LINE;x++)
        if(process_list[x].pid == pid)
        { 
            process_list[x].pid = 0, process_list[x].process_name = NULL;
            bg_idx--;
            return 0;    
        }
    return -1;
}

int add_process(int pid, char * name){
    for(int x=0;x<MAX_LINE;x++)
        if(process_list[x].pid == 0){
            process_list[x].pid = pid, process_list[x].process_name = name;
            bg_idx++;
            return 0;
        }
    return -1;

}

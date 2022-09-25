#ifndef __SIGNALS_H
#define __SIGNALS_H

typedef struct processList processList;

struct processList{
    int pid;
    char *process_name;
};

void init_process_list();
int add_process(int pid, char* name);
int remove_process(int pid);
char* get_process_name(int pid);
void ctrlC();
void ctrlZ();

#endif

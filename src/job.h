#ifndef __JOB_H
#define __JOB_H

#include "signals.h"

typedef struct sortedProcessList sortedProcessList;

struct sortedProcessList{
    processList process;
    int idx;
};


int job_cmd(int argc, char **arg_list);

#endif

#include "headers.h"
#include "job.h"

int job_cmd(int argc, char **arg_list)
{

    bool flag_r = false, flag_s = false;
    // check for flags
    for (int i = 1; i < argc; i++)
    {
        char *token = arg_list[i];
        if (token[0] == '-')
        {
            for (int i = 1; i < strlen(token); i++)
            {
                if (token[i] == 'r')
                {
                    flag_r = true;
                }
                else if (token[i] == 's')
                {
                    flag_s = true;
                }
                else
                {
                    fprintf(stderr, "job: invalid flag -- '%c'", token[i]);
                    return -1;
                }
            }
        }
    }

    // copy all elements of process_list to temp
    
    sortedProcessList sorted_process_list[bg_idx];
    for (int i = 0; i < bg_idx; i++)
    {
        sorted_process_list[i].process = process_list[i];
        sorted_process_list[i].idx = i + 1;
    }

    // sort temp according to process_name
    for (int i = 0; i < bg_idx; i++)
    {
        for (int j = i + 1; j < bg_idx; j++)
        {
            if (strcmp(sorted_process_list[i].process.process_name, sorted_process_list[j].process.process_name) > 0)
            {
                sortedProcessList temp = sorted_process_list[i];
                sorted_process_list[i] = sorted_process_list[j];
                sorted_process_list[j] = temp;
            }
        }
    }

    // print process list in the form of [job number] status - Running or Stopped  process name [process id]
    for (int i = 0; i < bg_idx; i++)
    {

        char *filePath = malloc(MAX_SIZE * sizeof(char));
        sprintf(filePath, "/proc/%d/stat", sorted_process_list[i].process.pid);

        int fd1 = open(filePath, O_RDONLY);

        // read buffers
        char *READ_BUFFER = malloc(MAX_SIZE * sizeof(char));
        char *temp;

        if (read(fd1, READ_BUFFER, MAX_SIZE) < 0)
        {
            perror("pinfo: Unable to read file\n");
            return -1;
        }

        if (close(fd1) < 0)
        {
            perror("pinfo: Unable to close the file\n");
            return -1;
        }

        strtok_r(READ_BUFFER, " \t", &temp);
        strtok_r(NULL, " \t", &temp);
        char *process_state = strtok_r(NULL, " \t", &temp);

        // check S and R - not sure if this is correct
        if (process_state[0] == 'S' || process_state[0] == 'R')
        {

            if (flag_r == true || flag_s == false)
            {
                printf("[%d] Running %s [%d]\n", sorted_process_list[i].idx, sorted_process_list[i].process.process_name, sorted_process_list[i].process.pid);
            }
        }
        else
        {
            if (flag_s == true || flag_r == false)
            {
                printf("[%d] Stopped %s [%d]\n", sorted_process_list[i].idx, sorted_process_list[i].process.process_name, sorted_process_list[i].process.pid);
            }
        }
        free(filePath);
    }

    return 0;
}

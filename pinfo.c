#include "headers.h"

// ADD + AFTER FINISHING FOREGROUND BACKGROUND

void pinfo_cmd(int argc, char **arg_list){
    int pid;

    // get the value of pid
    if(argc == 1){
        pid = (int)(getpid());
    }
    else if(argc == 2){
        // if(isdigit(arg_list[1]))
        //     pid = atoi(arg_list[1]);
        // else
        // perror("pinfo: Invalid arguement.\n");

        pid = atoi(arg_list[1]);

    }
    else {
        perror("pinfo: Too many arguements\n");
        return;        
    }
    
    char *filePath = malloc(MAX_SIZE * sizeof(char));
    sprintf(filePath, "/proc/%d/stat", (int)pid); 

    int fd = open(filePath, O_RDONLY);

    // read buffers
    char *READ_BUFFER = malloc(MAX_SIZE * sizeof(char));
    char* temp;

    if(read(fd, READ_BUFFER, MAX_SIZE)<0){
        perror("pinfo: Unable to read file\n");
        return;
    }

    if(close(fd) < 0)
        perror("pinfo: Unable to close the file\n");

    printf("%s", READ_BUFFER);

    char* process_state = strtok_r(READ_BUFFER, " \t", &temp);
    process_state = strtok_r(NULL, " \t", &temp);
    process_state = strtok_r(NULL, " \t", &temp);

    // printf("pid: %d\nprocess status: %s\nmemory: %s\nexecutable Path: %s\n",pid, process_state);

    free(filePath);
    free(READ_BUFFER);
    return;
}

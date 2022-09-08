#include "headers.h"


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

    int fd1 = open(filePath, O_RDONLY);

    // read buffers
    char *READ_BUFFER = malloc(MAX_SIZE * sizeof(char));
    char* temp;

    if(read(fd1, READ_BUFFER, MAX_SIZE)<0){
        perror("pinfo: Unable to read file\n");
        return;
    }

    if(close(fd1) < 0)
        perror("pinfo: Unable to close the file\n");


    // check if first element of read buffer is equal to the last element of the pid

    char *stat_1 = strtok_r(READ_BUFFER, " \t", &temp);
    strtok_r(NULL, " \t", &temp);
    char *process_state = strtok_r(NULL, " \t", &temp);

    char *stat_7;
    for(int i =0; i<5; i++)
        stat_7 = strtok_r(NULL, " \t", &temp);
    
    if(strcmp(stat_1, stat_7) == 0){
        strcat(process_state, "+");
    }

    printf("pid: %d\nprocess status: %s\n",pid, process_state);


    sprintf(filePath, "/proc/%d/statm", (int)pid);
    int fd2 = open(filePath, O_RDONLY);

    if(read(fd2, READ_BUFFER, MAX_SIZE)<0){
        perror("pinfo: Unable to read file\n");
        return;
    }

    if(close(fd2) < 0)
        perror("pinfo: Unable to close the file\n");


    char *memory = strtok(READ_BUFFER, " ");


    char buf[MAX_SIZE];
    char exe_path[MAX_SIZE];
    sprintf(buf,"/proc/%d/exe",pid);
    
    int len;

    if( (len = readlink(buf,exe_path,sizeof(exe_path))) <=0){
        perror("readlink");
        return;
    }

    exe_path[len] = 0;

    printf("memory: %s\nexecutable Path: %s\n",memory, exe_path);

    free(filePath);
    free(READ_BUFFER);
    return;
}

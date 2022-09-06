#include "headers.h"
#include "execvp.h"
#include "signals.h"

void execvp_cmd(int argc, char **arg_list){

    arg_list[argc] = NULL;

    bool bg_flag= false;

    for(int i = 0; i<argc; i++)
    {   
        // printf("%s\n",arg_list[i]);
        // check for background process
        if(strcmp(arg_list[i], "&") == 0)
        {
            bg_flag = true;
            arg_list[i] = NULL;
            break;
        }
        else if(strchr(arg_list[i],'&')){
            bg_flag = true;
            char *temp = strchr(arg_list[i],'&');
            *temp = '\0';
            break;
        }  
    }
    pid_t forkReturn = fork();
    if(forkReturn < 0)
    {
        perror("fork failed");
        return;
    }

    // child process - execute command
    else if(forkReturn == 0)
    {
        setpgid(0, 0);
        int q = execvp(arg_list[0],arg_list);
        if(q == -1)
        {
            fprintf(stderr, "%s: Command not found\n",arg_list[0]);
            return;
        }

        return;
        
    }
    // parent process - wait for child to finish
    else
    {
        if(bg_flag == false)
        {
            int status;
            waitpid(forkReturn, &status, WUNTRACED);
        }
        else
        {
            printf("[%d] %d\n", bg_idx + 1, forkReturn);
            if(add_process(forkReturn,arg_list[0]) == -1)
                fprintf(stderr,"Unable to add process\n");
            setpgid(0,0);
        }
    }

}
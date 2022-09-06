#include "headers.h"
#include "signal.h"
#include "prompt.h"

void finish_bg(){
    int status;
    pid_t child_pid = waitpid(-1, &status, WNOHANG | WUNTRACED);;
 
    if(child_pid > 0)
    { 
        for(int x=0;x<MAX_LINE;x++){
            if(child_pid == process_list[x].pid){
                if (WIFEXITED(status)){
                    fprintf(stderr,"\n%s with pid %d exited normally\n", get_process_name(child_pid), child_pid);
                    prompt();

                }
                else if (WIFSTOPPED(status)){
                    fprintf(stderr,"\n%s with pid %d suspended normally\n", get_process_name(child_pid), child_pid);
                    prompt();

                }
                else {
                    fprintf(stderr,"\n%s with pid %d exited abnormally\n", get_process_name(child_pid), child_pid);
                    prompt();
                }
                if(remove_process(child_pid) == -1)
                    {
                        fprintf(stderr,"\nCouldn't remove process\n");
                        prompt();

                    }
            }
            fflush(stdout);
        }
    }
    else
        return;
}

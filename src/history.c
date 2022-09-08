#include "headers.h"
#include "history.h"


// for now - remove/change
int file_exists(char *path)
{
    FILE *f = fopen(path,"r+");
    if(f==NULL)
        return 0;
    fclose(f);
    return 1;
}

void load_history(){

    for(int i=0;i<MAX_HISTORY;i++)
        history[i] = NULL;

    if(file_exists(history_path)){
        
        FILE *f = fopen(history_path,"r");

        char *cmd = NULL;
        size_t sz = MAX_SIZE;
        int hist_idx = 0;
        
        while (getline(&cmd,&sz,f)!=-1){
            char *temp = malloc(MAX_SIZE*sizeof(char));
            strcpy(temp,cmd);
            history[hist_idx] = temp;
            hist_idx++;
        }

        fclose(f);
    }

    return;
}

void store_history(char *command){

    // dont add repeated
    if(history[0])
        if(strcmp(history[0], command) == 0)
            return;

    for(int i = MAX_HISTORY-1;i>0; i--){
        history[i] = history[i-1];
    }

    char *temp = malloc(MAX_SIZE*sizeof(char));
    strcpy(temp,command);
    history[0] = temp;

    FILE *f = fopen(history_path,"w");
    for(int x=0;x<MAX_HISTORY;x++){
        if(history[x]!=NULL)
        {
            fprintf(f,"%s",history[x]);
        }
    }
    fclose(f);
    return;
}
void display_history(int num){
    // int x = num - 1;
    // while(x>=0 && history[x] != NULL){
    //     printf("%s", history[x]);
    //     x--;
    // }

    for(int x=0;x<num;x++)
        if(history[num-x]!=NULL)
            printf("%s", history[num-x]);
}

void history_cmd(int argc, char **arg_list){
    int display_num = 0;
    if(argc == 1){
        display_num = 10;
    }
    else if(argc == 2){
        // debug - if not integer
        if(0){
        // if(isdigit(arg_list[1]) == 0){
            fprintf(stderr, "history: Invalid arguement.\n");
            return; 
        }
        else{
            display_num = atoi(arg_list[1]);
            if(display_num>20){
              fprintf(stderr, "history: Can print only 20 .\n");
            }   
        }
    }
    else {
        fprintf(stderr, "history: Invalid number of arguements.\n");
        return;
    }

    display_history(display_num);
    return;
}

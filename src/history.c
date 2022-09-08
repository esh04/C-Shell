#include "headers.h"
#include "history.h"

void load_history(){

    for(int i=0;i<MAX_HISTORY;i++)
        history[i] = NULL;

    if(file_exists(history_path)){
        
        FILE *f = fopen(history_path,"r");

        if(f = NULL)
        {
            fprintf(stderr,"history: cannot open file to read\n");
            return
        }


        char *cmd = NULL;
        size_t sz = MAX_SIZE;
        int hist_idx = 0;
        
        while (getline(&cmd,&sz,f)!=-1){
            char *temp = malloc(MAX_SIZE*sizeof(char));
            strcpy(temp,cmd);
            history[hist_idx++] = temp;
        }

        if(fclose(f) != 0)
        {
            fprintf(stderr, "history: could not close the file.\n");
        }
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

    if(f == NULL)
    {
        fprintf(stderr, "history: could not open file to write.\n");
    }

    for(int x=0;x<MAX_HISTORY;x++){
        if(history[x]==NULL)
            continue;
        fprintf(f,"%s",history[x]);
        
    }

    if(fclose(f) != 0)
    {
        fprintf(stderr, "history: could not close the file.\n");
    }
    return;
}
void display_history(int num){
    // int x = num - 1;
    // while(x>=0 && history[x] != NULL){
    //     printf("%s", history[x]);
    //     x--;
    // }

    for(int i=0;i<num;i++)
        if(history[num-i]==NULL)
        {
            continue;
        }
        printf("%s", history[num-x]);

}

void history_cmd(int argc, char **arg_list){
    int display_num = 0;
    if(argc == 1){
        display_num = 10;
    }
    else if(argc == 2){
        display_num = atoi(arg_list[1]);
        if(display_num>20){
            fprintf(stderr, "history: Can print only 20 .\n");
        }
    }
    else {
        fprintf(stderr, "history: Invalid number of arguements.\n");
        return;
    }

    display_history(display_num);
    return;
}

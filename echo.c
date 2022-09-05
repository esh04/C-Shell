#include "headers.h"

void echo_cmd(int argc, char **arg_list){

    if(arg_list[1]==NULL){
		printf("\n");
	}
	else{
        // printf("%s", arg_list[1]);
        for(int i = 1; i< argc; i++){
            if(arg_list[i]){
                printf(" %s", arg_list[i]);
            }
        }

        printf("\n");    
    }   
	return;

}

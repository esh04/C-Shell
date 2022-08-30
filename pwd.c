#include "headers.h"

void pwd_cmd(){
    printf("%s\n",getcwd(NULL,0));
}
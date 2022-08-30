#include "headers.h"
#include "prompt.h"
#include "parse.h"

int main()
{
    // store home directory
    home = getcwd(NULL,0);
    prev_dir = NULL;
    while (1)
    {
        prompt();
        char *line = NULL;
        size_t sz = MAX_SIZE;

        ssize_t flag1 = getline(&line,&sz,stdin);

        parse(line);
    }
}

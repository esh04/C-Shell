#include "headers.h"
#include "prompt.h"
#include "parse.h"

int main()
{
    // store home directory
    home = getcwd(NULL,0);

    while (1)
    {
        prompt();
        // char line[200];
        char *line = NULL;
        size_t sz = 1000;

        // scanf("%s", line);
        ssize_t flag1 = getline(&line,&sz,stdin);

        parse(line);
    }
}

#include "headers.h"
#include "prompt.h"

int main()
{
    // store home directory
    home = getcwd(NULL,0);
    while (1)
    {
        prompt();
        char a[20];
        scanf("%s", a);
        // TAKE INPUT HERE
    }
}

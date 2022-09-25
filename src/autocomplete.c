#include "headers.h"
#include "ls.h"
#include "execvp.h"
#include "prompt.h"

int isSubstring(char *s1, char *s2)
{
    int M = strlen(s1);
    int N = strlen(s2);

    for (int i = 0; i <= N - M; i++)
    {
        int j;

        for (j = 0; j < M; j++)
            if (s2[i + j] != s1[j])
                break;

        if (j == M)
            return i;
    }

    return -1;
}

void autocomplete(char *input)
{

    char *string = malloc(MAX_SIZE * (sizeof(char))), *subtoken, *ptr2;

    strcpy(string, input);

    char **commands = (char **)(malloc(MAX_LINE * (sizeof(char *))));
    subtoken = strtok_r(string, " \t\r\n\a", &ptr2);
    int argc = 0;
    commands[0] = NULL;
    while (subtoken != NULL)
    {
        commands[argc++] = subtoken;
        subtoken = strtok_r(NULL, " \t\r\n\a", &ptr2);
    }

    struct dirent *d;

    DIR *dh = opendir(".");
    if (!dh)
    {
        fprintf(stderr, "autocomplete: Can't open directory.\n");
        return;
    }

    int check;
    if (argc - 1 < 0)
        check = 0;
    else
        check = argc - 1;

    int num = 0;
    char *temp = malloc(MAX_LINE * (sizeof(char)));
    while ((d = readdir(dh)) != NULL)
    {
        // check if commands[check] is a substring of d->d_name

        if (isSubstring(commands[check], d->d_name) != -1)
        {
            if (num == 0)
            {
                strcpy(temp, d->d_name);
            }
            else if (num == 1)
            {
                printf("\n%s", temp);
                printf("\n%s", d->d_name);
            }
            else
            {
                printf("\n%s", d->d_name);
            }
            num++;
        }
    }
    printf("\n");

    if (num == 1)
    {
        if (argc > 1)
        {
            strcpy(input_buffer, commands[0]);
            strcat(input_buffer, " ");
            for (int i = 1; i < argc - 1; i++)
            {
                strcat(input_buffer, commands[i]);
                strcat(input_buffer, " ");
            }

            strcat(input_buffer, temp);
        }
        else
        {
            strcpy(input_buffer, temp);
        }
        strcat(input_buffer, " ");
    }

    free(commands);
    free(string);
    free(temp);

    prompt();
    return;
}

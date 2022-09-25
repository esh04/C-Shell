#include "headers.h"
#include "echo.h"
#include "pwd.h"
#include "cd.h"
#include "pinfo.h"
#include "ls.h"
#include "history.h"
#include "execvp.h"
#include "discover.h"
#include "redirect.h"
#include "sig.h"
#include "job.h"
#include "bg.h"
#include "fg.h"


void execute(char *commands[], int argc)
{
    // execute command here
    if (strcmp(commands[0], "echo") == 0)
        echo_cmd(argc, commands);
    else if (strcmp(commands[0], "pwd") == 0)
        pwd_cmd();
    else if (strcmp(commands[0], "cd") == 0)
        cd_cmd(argc, commands);
    else if (strcmp(commands[0], "pinfo") == 0)
        pinfo_cmd(argc, commands);
    else if (strcmp(commands[0], "ls") == 0)
        ls_cmd(argc, commands);
    else if (strcmp(commands[0], "history") == 0)
        history_cmd(argc, commands);
    else if (strcmp(commands[0], "discover") == 0)
        discover_cmd(argc, commands);
    else if (strcmp(commands[0], "sig") == 0)
        sig_cmd(argc, commands);
    else if (strcmp(commands[0], "jobs") == 0)
        job_cmd(argc, commands);
    else if (strcmp(commands[0], "bg") == 0)
        bg_cmd(argc, commands);
    else if (strcmp(commands[0], "fg") == 0)
        fg_cmd(argc, commands);
    else if (strcmp(commands[0], "exit") == 0)
        exit(0);
    else
        execvp_cmd(argc, commands);

    return;
}
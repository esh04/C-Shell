#ifndef __HISTORY_H
#define __HISTORY_H

void load_history();
void store_history(char *command);
void display_history(int num);
void history_cmd(int argc, char **arg_list);

#endif

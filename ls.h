#ifndef __LS_H
#define __LS_H

struct dirent;

void display_dir(char *path, bool flag_a, bool flag_l, struct stat buf);
void display_file(char *path, bool flag_l, struct stat buf);
void ls_cmd(int argc, char **arg_list);

#endif
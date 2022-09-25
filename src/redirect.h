#ifndef __REDIRECT_H
#define __REDIRECT_H

int input_redirect(char * file);
int output_redirect(char * file);
int append_redirect(char * file);
void restore_dup();
void redirect(char *commands[], int argc);

#endif

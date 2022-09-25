#ifndef __PARSE_H
#define __PARSE_H

void parse_token(char *input);
int parse_pipes(char *input);
void parse();

#define DELIM1 ";\n"
#define DELIM3 "&"
#define DELIM2 " \t\r\n\a"

#endif

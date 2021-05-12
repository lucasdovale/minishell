// CES-33: Operating Systems
// Prof. Lourenco A Pereira
// Lab 2 - The mini-shell project
// Written by Lucas do Vale Bezerra, COMP-22

#ifndef PARSE_H 
#define PARSE_H

#include "pipes.h"

char* removeSpaces(char* str);
void parsing_cmd(char str[], Node *nodes);
void parsing_pipes(char str[]);
int breakString(char str[], char *breaks[], char regEx[]);
int breakStringInput(char str[], char *breaks[], char regEx[]);
int breakStringOutput(char str[], char *breaks[], char regEx[]);
void big_shell(char str[]);

#endif

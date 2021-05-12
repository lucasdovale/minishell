// CES-33: Operating Systems
// Prof. Lourenco A Pereira
// Lab 2 - The mini-shell project
// Written by Lucas do Vale Bezerra, COMP-22

#include "parse.c"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    printf("Welcome to the mini-shell! :D\n\n");

    char str[999];
    while(1) {
        write(0, "cmd> ", 5);
        int t = read(STDIN_FILENO, str, 999);
        str[t - 1] = '\0';
        big_shell(str);
    }

	return 0;
}

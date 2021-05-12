// CES-33: Operating Systems
// Prof. Lourenco A Pereira
// Lab 2 - The mini-shell project
// Written by Lucas do Vale Bezerra, COMP-22

#include "parse.h"
#include "pipes.c"
#include "execute.c"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


char* removeSpaces(char* str)
{
    static char str1[99];
    int count = 0, j, k;
  
    while (str[count] == ' ') {
        count++;
    }
  
    for (j = count, k = 0;
         str[j] != '\0'; j++, k++) {
        str1[k] = str[j];
    }
    str1[k] = '\0';
  
    return str1;
}

void parsing_cmd(char str[], Node *p) {
    // printf("FAZENDO parsing_cmd do comando: %s\n", str);
    char *argsInput[2];
    int hasInput = breakStringInput(str, argsInput, "<");

    char *argsOutput[2];
    int hasOutput = breakStringOutput(str, argsOutput, ">");

    if (hasInput > 1) {
        // printf("argsInput[0]: %s\n", argsInput[0]);
        // printf("argsInput[1]: %s\n", argsInput[1]);
        p->argsCount = breakStringInput(argsInput[0], p->args, " ");
        strcpy(p->cmd, p->args[0]);
        for(int i = 0; i < p->argsCount; i++) {
            // strcpy(p->args[i], removeSpaces(p->args[i]));
            // printf("args[%d]: %s\n", i, p->args[i]);
        }
        // printf("argsInput[1] (denovo): %s\n", argsInput[1]);
        p->file_in = argsInput[1];
        // printf("p->cmd: %s\n", p->cmd);
        // printf("p->file_in: %s\n", p->file_in);
    } else if (hasOutput > 1)  {
        p->argsCount = breakStringOutput(argsOutput[0], p->args, " ");
        strcpy(p->cmd, p->args[0]);
        for(int i = 0; i < p->argsCount; i++)
            strcpy(p->args[i], p->args[i]);
        p->file_out = argsOutput[1];
    }
    else {
        p->argsCount = breakString(str, p->args, " ");
        strcpy(p->cmd, p->args[0]);
        for(int i = 0; i < p->argsCount; i++)
            strcpy(p->args[i], p->args[i]);
    }
    // printf("\n\n");
}


void parsing_pipes(char str[]) {
    
    char *commands[50];
    int pipes = breakString(str, commands, "|");
    // // printf("COMANDOSSSS\n");
    // for(int i = 0; i < pipes; i++)
    //     // printf("commands[%d]: %s\n", i, commands[i]);
    // // printf("pipes = %d \n\n", pipes);
    Node *nodes = allocation_process(pipes);

    for(int i = 0; i < pipes; i++)
        parsing_cmd(commands[i], &nodes[i]);
        

    // for(int i = 0; i < pipes; i++) {
    //     // printf("----- Node %d -----\n", i);
    //     // printf("cmd: %s\n", nodes[i].cmd);
    //     // printf("argsCount = %d \n", nodes[i].argsCount);
    //     for(int i = 0; i < nodes[i].argsCount; i++) 
    //         // printf("args[%d]: %s\n", i, nodes[i].args[i]);
    //     // printf("file_in: %s\n", nodes[i].file_in);
    //     // printf("file_out: %s\n", nodes[i].file_out);
    //     // printf("pipe in: %s\n", nodes[i].in->cmd);
    //     // printf("pipe out: %s\n", nodes[i].out->cmd);
    //     // printf("\n\n");
    // }


    recursive_exec(&nodes[pipes - 1]);
    free(nodes);
}


int breakString(char str[], char *breaks[], char regEx[])
{
    char *strCut;
    strCut = strtok(str, regEx);
    int i = 0;
    while (strCut != NULL)
    {
        breaks[i] = strCut;
        strCut = strtok(NULL, regEx);
        i++;
    }
    return i;
}

int breakStringInput(char str[], char *breaks[], char regEx[])
{
    char *strCut;
    strCut = strtok(str, regEx);
    int i = 0;
    while (strCut != NULL)
    {
        breaks[i] = strCut;
        strCut = strtok(NULL, " <");
        i++;
    }
    return i;
}

int breakStringOutput(char str[], char *breaks[], char regEx[])
{
    char *strCut;
    strCut = strtok(str, regEx);
    int i = 0;
    while (strCut != NULL)
    {
        breaks[i] = strCut;
        strCut = strtok(NULL, " >");
        i++;
    }
    return i;
}

void big_shell(char str[]) {
    pid_t child = fork();
    if (child == 0) parsing_pipes(str);
    else wait(NULL);
}

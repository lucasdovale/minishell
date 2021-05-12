// CES-33: Operating Systems
// Prof. Lourenco A Pereira
// Lab 2 - The mini-shell project
// Written by Lucas do Vale Bezerra, COMP-22

#ifndef PIPES_H 
#define PIPES_H

typedef struct node Node;

struct node
{
    char cmd[50];
    char* args[50];
    int argsCount;
    char* file_in;
    char* file_out;
    Node* in;
    Node* out;
};

void init_process(Node* p);

Node* allocation_process(int size);

void pipes(Node *processes, int size);

#endif

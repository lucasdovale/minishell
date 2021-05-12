// CES-33: Operating Systems
// Prof. Lourenco A Pereira
// Lab 2 - The mini-shell project
// Written by Lucas do Vale Bezerra, COMP-22

#include "pipes.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void init_process(Node *p) {
    p->argsCount = 0;
    p->in = NULL;
    p->out = NULL;
    p->file_in = NULL;
    p->file_out = NULL;
}

Node* allocation_process(int size) {
    Node *nodes;
    nodes = malloc(size * sizeof(Node));

    for (int i = 0; i < size; i++)  init_process(&nodes[i]);
    if (size > 1)   pipes(nodes, size);

    return nodes;
}

void pipes(Node *nodes, int size) {
    for (int i = 0; i < size; i++) {
        if (i == 0) nodes[i].out = &nodes[i + 1];
        else if (i == size - 1) nodes[i].in = &nodes[i - 1];
        else {
            nodes[i].out = &nodes[i + 1];
            nodes[i].in = &nodes[i - 1];
        }
    }
}

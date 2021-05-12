// CES-33: Operating Systems
// Prof. Lourenco A Pereira
// Lab 2 - The mini-shell project
// Written by Lucas do Vale Bezerra, COMP-22

#include "execute.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>


void recursive_exec(Node *p) {
    int fd;
    if (p->in == NULL) { // último filho 
        if (p->file_in != NULL) {
            fd = open(p->file_in, O_RDONLY);
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        if (p->out == NULL) { // é orfão
            if (p->file_out != NULL) {
                fd = open(p->file_out, O_WRONLY | O_CREAT | O_TRUNC, 0666);
                dup2(fd, STDOUT_FILENO);
                dup2(fd, STDERR_FILENO);
                close(fd);
            }
        }
        // printf("Executa comando: %s\n", p->cmd);
        execve(p->cmd, p->args, NULL);
    }
    else {
        int pipe_fd[2];
        if (p->out == NULL) { // pai de todos
            if (p->file_out != NULL) {
                fd = open(p->file_out, O_WRONLY | O_CREAT | O_TRUNC, 0666);
                dup2(fd, STDOUT_FILENO);
                dup2(fd, STDERR_FILENO);
                close(fd);
            }
        }
        pipe(pipe_fd);
        if (fork() == 0) { // filho
            close(pipe_fd[0]);
            dup2(pipe_fd[1], STDOUT_FILENO);
            recursive_exec(p->in);
        }
        else { // pai
            close(pipe_fd[1]);
            dup2(pipe_fd[0], STDIN_FILENO);
            int status;
            wait(&status);
            execve(p->cmd, p->args, NULL);
        }
    }
}

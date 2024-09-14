#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h>
#include "minishell.h"

#define MSGSIZE 16 
char* msg1 = "hello, world #1"; 
char* msg2 = "hello, world #2"; 
char* msg3 = "hello, world #3"; 
  
  
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void pipe_pipe(char **commands) {
    int num_cmds = 0;
    int i = 0;
    
    // Count the number of commands
    while (commands[num_cmds] != NULL) {
        num_cmds++;
    }

    int pipefds[2 * (num_cmds - 1)];
    pid_t pid;

    // Create pipes
    for (i = 0; i < num_cmds - 1; i++) {
        if (pipe(pipefds + i * 2) == -1) {
            perror("pipe failed");
            exit(EXIT_FAILURE);
        }
    }

    int cmd_idx = 0;

    // Fork and execute commands
    for (cmd_idx = 0; cmd_idx < num_cmds; cmd_idx++) {
        pid = fork();
        if (pid == 0) {  // Child process
            // If not the first command, redirect stdin to the previous pipe
            if (cmd_idx > 0) {
                dup2(pipefds[(cmd_idx - 1) * 2], STDIN_FILENO);
            }

            // If not the last command, redirect stdout to the next pipe
            if (cmd_idx < num_cmds - 1) {
                dup2(pipefds[cmd_idx * 2 + 1], STDOUT_FILENO);
            }

            // Close all pipe file descriptors
            for (i = 0; i < 2 * (num_cmds - 1); i++) {
                close(pipefds[i]);
            }

            // Split the command into arguments for execvp
            char *cmd_args[10];  // You can increase this limit based on your use case
            char *token = strtok(commands[cmd_idx], " ");
            int arg_idx = 0;
            while (token != NULL) {
                cmd_args[arg_idx++] = token;
                token = strtok(NULL, " ");
            }
            cmd_args[arg_idx] = NULL;

            // Execute the command
            execvp(cmd_args[0], cmd_args);
            perror("exec failed");
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }
    }

    // Close all pipes in the parent
    for (i = 0; i < 2 * (num_cmds - 1); i++) {
        close(pipefds[i]);
    }

    // Wait for all child processes to finish
    for (i = 0; i < num_cmds; i++) {
        wait(NULL);
    }
}
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void pipe_own(char **tree)
{
    int i = 0;
    int fd[2];
    int in_fd = 0; // Used for the input to the current process (starts as STDIN)

    while (tree[i])
    {
        pipe(fd);  // Create a new pipe

        // Fork a new process for each command
        if (fork() == 0)
        {
            // Child process
            
            // If there's input from the previous command, set it up
            dup2(in_fd, STDIN_FILENO);
            if (tree[i + 1] != NULL) // If not the last command
            {
                dup2(fd[1], STDOUT_FILENO); // Set the pipe output for current command
            }

            // Close pipes in child
            close(fd[0]);
            close(fd[1]);

            // Execute the command
            system(tree[i]);
            exit(1);
        }
        else
        {
            // Parent process
            close(fd[1]); // Close the write end of the pipe (not needed)

            // Keep the read end for the next command
            in_fd = fd[0];

            i++;
        }
    }
}

int main(int ac, char **av)
{
    if (ac > 1)
        pipe_own(av + 1);  // Pass the command list excluding the program name

    return 0;
}

 
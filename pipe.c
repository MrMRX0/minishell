#include "minishell.h"

void pipe_pipe(char ***commands, int n, t_data *data)
{
    int i = 0;
    pid_t pid;
    int *fd = malloc(((2 * n)  * sizeof(int)));
    int cmd_idx = 0;


    while(i < n)
    {
        if (pipe(fd + i * 2) == -1)
        {
            perror("pipe failed");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    // Fork and execute commands
    while(cmd_idx <= n)
    {
        pid = fork();
        if (pid == 0)
        {
            // If not the first command, redirect stdin to the previous pipe
            if (cmd_idx > 0)
                dup2(fd[(cmd_idx - 1) * 2], STDIN_FILENO);
            // If not the last command, redirect stdout to the next pipe
            if (cmd_idx < n)
                dup2(fd[cmd_idx * 2 + 1], STDOUT_FILENO);
            // Close all pipe file descriptors
            i = 0;
            while(i < 2 * n)
            {
                close(fd[i]);
                i++;
            }
            execute(commands[cmd_idx], data->env);
            i = 0;
            while(commands[cmd_idx][i])
            {
                free(commands[cmd_idx][i]);
                i++;
            }
            free(commands[cmd_idx]);
            exit(0);
        }
        else if (pid < 0) 
        {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }
        else
        {
            usleep(1000);
            cmd_idx++;
        }
    }
    // Close all pipes in the parent
    i = 0;
    while(i < 2 * n)
    {
        close(fd[i]);
        i++;
    }
    // Wait for all child processes to finish
    i = 0;
    while(i <= n)
    {
        wait(NULL);
        i++;
    }
    // printf("number of executions is %d\n", cmd_idx);
}

 
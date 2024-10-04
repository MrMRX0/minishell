/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 04:21:45 by ibougajd          #+#    #+#             */
/*   Updated: 2024/10/03 10:09:24 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void pipe_pipe(int n, t_data *data)
{
	int i = 0;
	pid_t pid;
	int *fd = malloc(((2 * n)  * sizeof(int)));
	int cmd_idx = 0;
	t_token *pipe_token;
	char **command = NULL;
	int std_out = 0;
	int std_in = 0;


	while(i < n)
	{
		if (pipe(fd + i * 2) == -1)
		{
			perror("pipe failed");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	t_token *tmp = data->token; // store token pointer to free it later
	// Fork and execute commands
	while(cmd_idx <= n)
	{
		pipe_token  = extract_token(&data->token);
		command = get_copy_of_token_v1(command, &pipe_token);
		expand(command,data, &pipe_token);
		join_nodes(&pipe_token);
		std_out = redirections(&pipe_token, data);
		std_in = redirect_input(&pipe_token, data);
		if(std_out == -1 || std_in == -1)
		{
			cmd_idx++;
			continue;
		}
		i = 0;
		while(command[i])
		{
			free(command[i]);
			i++;
		}
		free(command);
		command = get_copy_of_token_v2(command, &pipe_token);
		free_linked_list(&pipe_token);
		pid = fork();
		if (pid == 0)
		{
			if(!std_in)
			{
				if (cmd_idx > 0)
					dup2(fd[(cmd_idx - 1) * 2], STDIN_FILENO);
			}
			if(!std_out)
			{
				if (cmd_idx < n)
					dup2(fd[cmd_idx * 2 + 1], STDOUT_FILENO);
			}
			i = 0;
			while(i < 2 * n)
			{
				close(fd[i]);
				i++;
			}
			if(ft_strcmp(command[0],"exit") == 0)
			{
				data->flag = 1;
				ft_exit(command,data);
			}
			execute(command, data);
			exit(0);
		}
		else if (pid < 0) 
		{
			perror("fork failed");
			exit(EXIT_FAILURE);
		}
		else
		{
			i = 0;
			while(command[i])
			{
				free(command[i]);
				i++;
			}
			free(command);
			restore_stdin_stdout(data->std_in, data->std_out);
			save_stdin_stdout(&data->std_in, &data->std_out);
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
	free(fd);
	// Wait for all child processes to finish
	i = 0;
	while(i <= n)
	{
		wait(NULL);
		i++;
	}
	data->token = tmp; // restore pointer
	// printf("number of executions is %d\n", cmd_idx);
}

 
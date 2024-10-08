/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 04:21:45 by ibougajd          #+#    #+#             */
/*   Updated: 2024/10/08 21:13:31 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incld/minishell.h"

int	*create_pipes(int n)
{
	int	i;
	int	*fd;

	i = 0;
	fd = ft_malloc(((2 * n) * sizeof(int)));
	while (i < n)
	{
		if (pipe(fd + i * 2) == -1)
		{
			perror("pipe failed");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (fd);
}

void	pipex(t_data *data, int n)
{
	t_pipex	pipe;
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = data->token;
	ft_memset(&pipe, 0, sizeof(t_pipex));
	pipe.fd = create_pipes(n);
	while (pipe.cmd_idx <= n)
	{
		pipe.command = get_command(data, &pipe.std_in, &pipe.std_out);
		if ((pipe.std_out == -1 || pipe.std_in == -1) && (++pipe.cmd_idx))
			continue ;
		ft_fork(&pipe, data, n);
	}
	close_fds(n, pipe.fd);
	while (i <= n)
	{
		wait(NULL);
		i++;
	}
	data->token = tmp;
}

void	pipex_child(t_pipex *pipe, t_data *data, int n)
{
	if (!pipe->std_in)
	{
		if (pipe->cmd_idx > 0)
			dup2(pipe->fd[(pipe->cmd_idx - 1) * 2], STDIN_FILENO);
	}
	if (!pipe->std_out)
	{
		if (pipe->cmd_idx < n)
			dup2(pipe->fd[pipe->cmd_idx * 2 + 1], STDOUT_FILENO);
	}
	close_fds(n, pipe->fd);
	if (ft_strcmp(pipe->command[0], "exit") == 0)
	{
		data->flag = 1;
		ft_exit(pipe->command, data);
	}
	execute(pipe->command, data);
	ft_free_all();
	exit(data->exit_status);
}

void	ft_fork(t_pipex *pipe, t_data *data, int n)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		pipex_child(pipe, data, n);
	else
	{
		if (pipe->cmd_idx == n)
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				data->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				data->exit_status = WTERMSIG(status) + 128;
		}
		restore_stdin_stdout(data->std_in, data->std_out);
		save_stdin_stdout(&data->std_in, &data->std_out);
		usleep(1000);
		pipe->cmd_idx++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:49:01 by ibougajd          #+#    #+#             */
/*   Updated: 2024/10/08 20:50:52 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incld/minishell.h"

void	normal_execution(t_data *data)
{
	char	**command;
	int		red_fd;
	int		red_in;

	command = NULL;
	red_fd = 0;
	red_in = 0;
	set_heredoc_input_value(&data->token);
	command = get_copy_of_token_v1(command, &(data->token));
	if (!command)
		return ;
	expand(command, data, &data->token);
	join_nodes(&data->token);
	red_fd = redirections(&data->token, data);
	red_in = redirect_input(&data->token, data);
	if (red_fd == -1 || red_in == -1)
		return ;
	command = get_copy_of_token_v2(command, &(data->token));
	if (!command)
		return ;
	execute(command, data);
}

void	execution(t_data *data)
{
	int	i;

	i = get_size_of_tree(&data->token);
	if (!i)
		normal_execution(data);
	else
		pipex(data, i);
}

void	child_process(char **args, t_data *data, char *path)
{
	struct stat	statbuf;

	stat(args[0], &statbuf);
	if (ft_strchr(args[0], '/'))
	{
		if (S_ISDIR(statbuf.st_mode))
		{
			ft_error(data, args[0], ": Is a directory\n", 126);
			exit(data->exit_status);
		}
		if (access(args[0], X_OK) == -1)
		{
			ft_error(data, args[0], ": No such file or directory\n", 127);
			exit(data->exit_status);
		}
		execve(args[0], args, data->env);
	}
	if (path)
		execve(path, args, data->env);
	else
	{
		ft_error(data, args[0], ": command not found\n", 127);
		exit(data->exit_status);
	}
}

void	parent_process(t_data *data, int pid)
{
	int	i;
	int	status;

	i = 0;
	restore_stdin_stdout(data->std_in, data->std_out);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->exit_status = WTERMSIG(status) + 128;
}

void	execute(char **args, t_data *data)
{
	int		i;
	char	*path;
	pid_t	pid;

	path = NULL;
	i = 0;
	g_global_data->sig_flag2 = 0;
	if (!args[0])
		return ;
	if (ft_strcmp(args[0], "cat") == 0 || ft_strcmp(args[0], "/bin/cat") == 0)
		g_global_data->sig_flag3 = 1;
	signal(SIGINT, handler_2);
	signal(SIGQUIT, handler_3);
	if (bultins(args, data))
		return ;
	path = check_path(args[0], data);
	pid = fork();
	if (pid == 0)
		child_process(args, data, path);
	else
		parent_process(data, pid);
}

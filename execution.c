/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:49:01 by ibougajd          #+#    #+#             */
/*   Updated: 2024/10/01 06:48:27 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	normal_execution(t_data *data)
{
	char **command;
	int red_fd = 0;
	int red_in = 0;

	command = NULL;
	set_heredoc_input_value(&data->token);
	command = get_copy_of_token(command, &(data->token)); //free command
	if(!command)
		return ;
	expand(command,data, &data->token);
	join_nodes(&data->token);
	red_fd = redirections(&data->token);
	red_in = redirect_input(&data->token, data);
	if(red_in)
		dup2(red_in, STDIN_FILENO);
	if (red_fd)
		dup2(red_fd, STDOUT_FILENO);
	command = get_copy_of_token_v3(command, &(data->token));
	if(!command)
		return;
	execute(command, data);
}


void execution(t_data *data)
{
	int		i;
	
	i = get_size_of_tree(&data->token);
	if (!i)
		normal_execution(data);
	else
		pipe_pipe(i, data);
}
void	execute(char **args, t_data *data)
{
		int i = 0;
	    signal(SIGINT, exec_handler);
		signal(SIGQUIT, SIG_IGN);
		if (ft_buitin_check(args) == 0)
		{
			bultins_runner(args,data);
			return ;
		}
		pid_t pid = fork();
		char *path = NULL;
		if (pid == 0)
		{
				if (strchr(args[0], '/'))
				{
					if (execve(args[0], args, data->env) == -1)
					{
						write(2, "minishell: ", 12);
						write(2, args[0], ft_strlen(args[0]));
						write(2, ": No such file or directory\n", 29);
						data->exit_status = 127;
						exit(data->exit_status);
					}
				}
				else if(check_path(args[0], data))
				{
					path = ft_strjoin("/bin/", args[0]);
					data->exit_status = 0;
					if (execve(path, args, data->env) == -1)
					{
						data->exit_status = 2;
						perror("Error");
						exit(data->exit_status);
					}
				}
				else
					ft_error(args, data);

			}
		else
		{
			restore_stdin_stdout(data->std_in, data->std_out);
			int status;
			
			waitpid(pid,&status, 0);
			if (WIFEXITED(status))
				data->exit_status = WEXITSTATUS(status); // Get the child's exit status
			// while(args[i])
			// {
			// 	free(args[i]);
			// 	i++;
			// }
			// free(args);
			
		}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 04:21:31 by ibougajd          #+#    #+#             */
/*   Updated: 2024/10/08 21:22:51 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incld/minishell.h"

int	redirect_input(t_token **token, t_data *data)
{
	int		fd;
	t_token	*tmp;

	tmp = *token;
	fd = 0;
	while (tmp)
	{
		if (tmp->type == HERDOK && g_global_data->sig_flag != 1)
		{
			fd = heredoc(&tmp, data);
			tmp = tmp->next->next;
		}
		else if (tmp->type == I_R)
		{
			fd = open(tmp->next->arg, O_RDONLY);
			if (access(tmp->next->arg, F_OK) == -1)
				return (ft_error(data, tmp->next->arg, NO_F_D, 1), -1);
			if (access(tmp->next->arg, R_OK) == -1)
				return (ft_error(data, tmp->next->arg, P_D, 1), -1);
			tmp = tmp->next->next;
		}
		else if (tmp)
			tmp = tmp->next;
	}
	return (dup2(fd, STDIN_FILENO), fd);
}

int	open_file(char *file_name, t_data *data, int mode)
{
	int	fd;

	fd = open(file_name, O_WRONLY | O_CREAT | mode, 0644);
	if (access(file_name, W_OK) == -1)
		return (ft_error(data, file_name, P_D, 1), -1);
	dup2(fd, STDOUT_FILENO);
	return (fd);
}

int	redirections(t_token **token, t_data *data)
{
	t_token	*tmp;
	int		fd;

	tmp = *token;
	fd = 0;
	while (tmp)
	{
		if ((tmp->next) && (tmp->type == S_R || tmp->type == A_R))
		{
			if (tmp->type == A_R)
				fd = open_file(tmp->next->arg, data, O_APPEND);
			else
				fd = open_file(tmp->next->arg, data, O_TRUNC);
			if (fd == -1)
				return (-1);
		}
		tmp = tmp->next;
	}
	return (fd);
}

void	*cut(t_data *data, char *command, char c)
{
	int	i;

	i = 0;
	while (command[i] != c)
		i++;
	data->type = 0;
	command = add_command_to_node(command, i, data);
	return (command);
}

char	*handle_redirections(char *command, t_data *data, char c)
{
	int	i;

	i = 0;
	if (command[i] != c)
		return (command = cut(data, command, c), command);
	while (command[i] == c)
		i++;
	if (i == 1)
	{
		data->type = I_R;
		if (c == '>')
			data->type = S_R;
		command = add_command_to_node(command, i, data);
	}
	else if (i == 2)
	{
		data->type = A_R;
		if (c == '<')
			data->type = HERDOK;
		command = add_command_to_node(command, i, data);
	}
	else
		return (data->syntax_error = 1, NULL);
	return (command);
}

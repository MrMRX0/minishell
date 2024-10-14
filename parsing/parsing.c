/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 14:48:47 by ibougajd          #+#    #+#             */
/*   Updated: 2024/10/14 01:23:35 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incld/minishell.h"

int	parser(t_data *data)
{
	t_token	*tmp;

	tmp = data->token;
	if (!tmp)
		return (0);
	if (tmp->type == PIPE)
		return (ft_syntax_error(data), 1);
	while (tmp)
	{
		if (tmp->type == S_R || tmp->type == A_R || tmp->type == HERDOK
			|| tmp->type == I_R)
		{
			if (!tmp->next)
				return (ft_syntax_error(data), 1);
			if (tmp->next->type == S_R || tmp->next->type == A_R)
				return (ft_syntax_error(data), 1);
			if (tmp->next->type == HERDOK || tmp->next->type == I_R)
				return (ft_syntax_error(data), 1);
			if (tmp->next->type == PIPE)
				return (ft_syntax_error(data), 1);
		}
		tmp = tmp->next;
	}
	return (0);
}

char	*split_the_command(char *command, int i, t_data *data)
{
	if (command[i] == ' ' || command[i] == '\0')
	{
		data->type = 0;
		command = add_command_to_node(command, i, data);
	}
	else if (command[i] == '\"')
		command = handle_quote(command, data, '\"');
	else if (command[i] == '\'')
		command = handle_quote(command, data, '\'');
	else if (command[i] == '>')
		command = handle_redirections(command, data, '>');
	else if (command[i] == '|')
		command = handle_pipe(command, data);
	else if (command[i] == '<')
		command = handle_redirections(command, data, '<');
	return (command);
}

int	parsing(char *command, t_data *data)
{
	int	i;

	i = 0;
	if (*command == '\n')
		return (data->exit_status = 0, 1);
	data->syntax_error = 0;
	while (command[i] != '\0')
	{
		command = remove_white_spaces(command);
		if (!command)
			return (0);
		while (command[i] != '\"' && command[i] != ' ' && command[i] != '\0'
			&& command[i] != '\'' && command[i] != '>' && command[i] != '|'
			&& command[i] != '<')
			i++;
		command = split_the_command(command, i, data);
		if (data->syntax_error)
			return (ft_syntax_error(data), 1);
		if (!command)
			return (0);
		i = 0;
	}
	return (0);
}

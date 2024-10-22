/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-bou <nait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:56:16 by ibougajd          #+#    #+#             */
/*   Updated: 2024/10/22 12:08:35 by nait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incld/minishell.h"

char	*func2(t_data *data, char *command, char c)
{
	int		i;
	t_token	*tmp;

	i = 0;
	while (command[i] != c)
		i++;
	data->type = 0;
	command = add_command_to_node(command, i, data);
	tmp = data->token;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next_command = 1;
	return (command);
}

char	*func3(t_data *data, char *command, char c, int i)
{
	char	letter;
	t_token	*tmp;

	letter = command[i];
	data->type = S_QUOTE;
	if (c == '\"')
		data->type = D_QUOTE;
	command = add_command_to_node(command, i, data);
	if (!command)
		return (NULL);
	tmp = data->token;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next_command = 0;
	if (letter != ' ' && letter != '\0' && letter != '>' && letter != '<'
		&& letter != '|')
		tmp->next_command = 1;
	return (command);
}

char	*func1(t_data *data, char *command, char c)
{
	int	quote;
	int	i;

	i = 1;
	quote = 1;
	while (command[i])
	{
		if (command[i] != c)
			i++;
		if (command[i] == c)
		{
			quote++;
			i++;
		}
		if ((quote % 2 == 0))
			return (command = func3(data, command, c, i), command);
	}
	data->syntax_error = 1;
	return (NULL);
}

char	*ft_remove_char_norm(char *new, char *str, char c)
{
	int	i;
	int	b;

	i = 0;
	b = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
			new[b++] = str[i++];
	}
	new[b] = '\0';
	return (new);
}

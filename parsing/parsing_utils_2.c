/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 17:15:08 by ibougajd          #+#    #+#             */
/*   Updated: 2024/10/04 20:56:21 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incld/minishell.h"

char	*handle_quote(char *command, t_data *data, char c)
{
	if (command[0] == c)
		return (command = func1(data, command, c), command);
	else
		return (command = func2(data, command, c), command);
	return (NULL);
}

void	ft_syntax_error(t_data *data)
{
	write(2, "syntax Error\n", 14);
	data->exit_status = 2;
}

char	*handle_pipe(char *command, t_data *data)
{
	int	i;
	int	b;

	i = 0;
	b = 0;
	while (command[i] != '|')
		i++;
	if (i)
		return (data->type = 0, command = add_command_to_node(command, i, data),
			command);
	i = 1;
	while (command[i] != '|' && command[i] != '\0')
	{
		if (command[i] == ' ')
			i++;
		else if (++b)
			i++;
	}
	if (b == 0)
		return (data->syntax_error = 1, NULL);
	data->type = PIPE;
	command = add_command_to_node(command, 1, data);
	return (command);
}

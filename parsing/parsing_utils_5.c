/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-bou <nait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 01:29:58 by nait-bou          #+#    #+#             */
/*   Updated: 2024/10/14 01:32:44 by nait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incld/minishell.h"

void	join_nodes(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp)
	{
		if (tmp->next_command == 1 && !tmp->next)
			return ;
		if (tmp->next_command == 1 && tmp->next)
			join_and_free(&tmp);
		if (tmp->next_command == 0)
			tmp = tmp->next;
	}
	tmp = *token;
	if (g_global_data->tmp_error_flag)
	{
		tmp->arg = ft_remove_char(tmp->arg, '\'');
		tmp->arg = ft_remove_char(tmp->arg, '\"');
	}
}

char	*add_command_to_node(char *command, int i, t_data *data)
{
	int		j;
	t_token	*tmp;

	j = 0;
	ft_lst_add(&data->token);
	tmp = data->token;
	while (tmp->next)
		tmp = tmp->next;
	tmp->arg = ft_malloc((i + 1) * sizeof(char));
	tmp->type = data->type;
	while (j < i)
	{
		tmp->arg[j] = command[j];
		j++;
	}
	tmp->arg[j] = '\0';
	if (!command[i])
		return (NULL);
	return (command + i);
}

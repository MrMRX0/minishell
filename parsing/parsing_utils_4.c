/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 20:46:42 by ibougajd          #+#    #+#             */
/*   Updated: 2024/10/14 02:06:46 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incld/minishell.h"

t_token	*extract_token(t_token **token)
{
	t_token	*new;
	t_token	*tmp;

	new = NULL;
	tmp = NULL;
	while ((*token) && (*token)->type != PIPE)
	{
		ft_lst_add(&new);
		tmp = new;
		while (tmp->next)
			tmp = tmp->next;
		tmp->arg = ft_strdup((*token)->arg);
		tmp->next_command = (*token)->next_command;
		tmp->type = (*token)->type;
		*token = (*token)->next;
	}
	if (*token)
		*token = (*token)->next;
	return (new);
}

void	join_and_free(t_token **tmp)
{
	t_token	*to_free;

	to_free = NULL;
	(*tmp)->arg = ft_strjoin((*tmp)->arg, (*tmp)->next->arg);
	to_free = (*tmp)->next;
	if (to_free->next)
		(*tmp)->next = to_free->next;
	else
		(*tmp)->next = NULL;
	(*tmp)->type = 0;
	if (to_free->next_command == 0)
		(*tmp)->next_command = 0;
}

char	*ft_remove_char(char *str, char c)
{
	int		i;
	int		b;
	char	*new;

	i = 0;
	b = 0;
	new = NULL;
	while (str[i++])
	{
		if (str[i] != c)
			b++;
	}
	if (!b)
		return (str);
	new = ft_malloc((b + 1) * sizeof(char));
	i = 0;
	b = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
			new[b++] = str[i++];
	}
	return (new[b] = '\0', new);
}

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
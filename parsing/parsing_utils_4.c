/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 20:46:42 by ibougajd          #+#    #+#             */
/*   Updated: 2024/10/06 01:50:30 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incld/minishell.h"

void	ft_lst_add(t_token **lst)
{
	t_token	*current;
	t_token	*new_node;

	if (!*lst)
	{
		*lst = ft_malloc(1 * sizeof(t_token));
		(*lst)->arg = NULL;
		(*lst)->next = NULL;
		(*lst)->previous = NULL;
		(*lst)->next_command = 0;
		return ;
	}
	current = *lst;
	while (current->next)
		current = current->next;
	new_node = ft_malloc(sizeof(t_token));
	new_node->arg = NULL;
	new_node->next = NULL;
	new_node->next_command = 0;
	current->next = new_node;
	new_node->previous = current;
}

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
	char	*to_free_2;

	to_free_2 = NULL;
	to_free = NULL;
	to_free_2 = (*tmp)->arg;
	(*tmp)->arg = ft_strjoin((*tmp)->arg, (*tmp)->next->arg);
	free(to_free_2);
	to_free = (*tmp)->next;
	if (to_free->next)
		(*tmp)->next = to_free->next;
	else
		(*tmp)->next = NULL;
	(*tmp)->type = 0;
	if (to_free->next_command == 0)
		(*tmp)->next_command = 0;
	free(to_free->arg);
	free(to_free);
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

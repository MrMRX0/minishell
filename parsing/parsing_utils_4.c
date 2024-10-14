/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-bou <nait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 20:46:42 by ibougajd          #+#    #+#             */
/*   Updated: 2024/10/14 01:41:46 by nait-bou         ###   ########.fr       */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 02:18:37 by soutchak          #+#    #+#             */
/*   Updated: 2024/10/06 02:31:45 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incld/minishell.h"

t_bool	fft_lstclear(t_cool **lst, void (*del)(void *))
{
	t_cool	*curr;
	t_cool	*head;

	if (del == NULL || lst == NULL || *lst == NULL)
		return (false);
	head = *lst;
	curr = head;
	while (head != NULL)
	{
		head = head->next;
		del(curr->content);
		curr->next = NULL;
		curr->prev = NULL;
		free(curr);
		curr = head;
	}
	*lst = NULL;
	return (true);
}

 t_cool	*fft_lstlast(t_cool *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_bool	fft_lstadd_back(t_cool **lst, t_cool *new)
{
	t_cool	*last;

	if (new == NULL || lst == NULL)
		return (false);
	if (*lst == NULL)
	{
		*lst = new;
		return (true);
	}
	last = fft_lstlast(*lst);
	last->next = new;
	new->prev = last;
	return (true);
}

t_cool	*fft_lstnew(void *content)
{
	t_cool	*newnode;

	newnode = (t_cool *)malloc(sizeof(t_cool));
	if (newnode == NULL)
		return (NULL);
	newnode->content = content;
	newnode->prev = NULL;
	newnode->next = NULL;
	return (newnode);
}

void	fft_lstdel_node(t_cool **lst, void (*del)(void *), t_cool *node)
{
	t_cool	*head;

	head = *lst;
	while (head)
	{
		if (head == node)
		{
			if (!head->prev)
			{
				*lst = head->next;
				if (*lst)
					(*lst)->prev = NULL;
			}
			else
			{
				head->prev->next = head->next;
				if (head->next)
					head->next->prev = head->prev;
			}
			if (del && head->content)
				del(node->content);
			return (head->content = NULL, free(node), node = NULL, (void)0);
		}
		head = head->next;
	}
}

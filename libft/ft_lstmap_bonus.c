/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:25:47 by ibougajd          #+#    #+#             */
/*   Updated: 2023/12/02 18:15:50 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*currentnode;
	void	*fcontent;

	if (!lst || !f || !del)
		return (NULL);
	new = NULL;
	while (lst)
	{
		fcontent = f(lst->content);
		currentnode = ft_lstnew(fcontent);
		if (!currentnode)
		{
			del(fcontent);
			ft_lstclear(&new, del);
			return (new);
		}
		ft_lstadd_back(&new, currentnode);
		lst = lst->next;
	}
	return (new);
}

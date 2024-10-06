/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gar_co.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 01:42:02 by ibougajd          #+#    #+#             */
/*   Updated: 2024/10/06 02:37:52 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incld/minishell.h"



void	ft_free_heap(void)
{
	t_cool	**head;

	head = &global_data->garn;
	fft_lstclear(head, free);
}

void	*ft_malloc(size_t size)
{
	t_cool	**head;
	t_cool	*tmp;
	void	*heap_block;

	head = &global_data->garn;
	heap_block = malloc(size);
	if (!heap_block)
	{
		ft_free_heap();
		perror("ft_malloc() failure!");
		exit(EXIT_FAILURE);
	}
	tmp = fft_lstnew(heap_block);
	if (!tmp)
	{
		ft_free_heap();
		perror("ft_malloc() failure!");
		exit(EXIT_FAILURE);
	}
	fft_lstadd_back(head, tmp);
	return (heap_block);
}

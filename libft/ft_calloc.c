/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:43:12 by ibougajd          #+#    #+#             */
/*   Updated: 2023/12/02 16:41:32 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;
	size_t	total_size;

	ptr = NULL;
	if (size > 0 && nmemb > 0)
	{
		total_size = nmemb * size;
		if (total_size / nmemb != size)
			return (NULL);
		ptr = malloc(total_size);
		if (!ptr)
			return (NULL);
		ft_bzero(ptr, total_size);
	}
	else if (size == 0 || nmemb == 0)
	{
		ptr = malloc(1);
		ptr[0] = 0;
		return ((void *)ptr);
	}
	return ((void *)ptr);
}

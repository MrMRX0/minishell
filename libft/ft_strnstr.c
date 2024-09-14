/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:28:04 by ibougajd          #+#    #+#             */
/*   Updated: 2023/12/01 15:54:43 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	b;
	size_t	i;
	size_t	c;

	i = 0;
	b = 0;
	c = 0;
	if (little[i] == '\0')
		return ((char *)big);
	while (i < len && big[i])
	{
		while (i < len && little[b] == big[c] && little[b])
		{
			b++;
			c++;
			if (c <= len && little[b] == '\0')
				return ((char *)big + i);
		}
		i++;
		c = i;
		b = 0;
	}
	return (0);
}

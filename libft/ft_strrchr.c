/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:03:48 by ibougajd          #+#    #+#             */
/*   Updated: 2023/12/01 15:54:19 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = ft_strlen(s);
	while (len && s[len] != (char)c)
		len--;
	if (s[len] == (char)c || (char)c == '\0')
		return ((char *)s + len);
	else
		return (NULL);
}

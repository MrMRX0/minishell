/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 21:21:58 by ibougajd          #+#    #+#             */
/*   Updated: 2024/10/06 02:42:57 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*all_str;
	int		n;
	int		i;
	int		total_len;

	if (!s2)
		return (NULL);
	if (!s1)
		return (all_str = ft_strdup(s2), all_str);
	total_len = ft_strlen(s1) + ft_strlen(s2);
	i = -1;
	all_str = (char *)ft_malloc(total_len * sizeof(char) + 1);
	if (!all_str)
		return (NULL);
	while (s1[++i] != '\0')
		all_str[i] = s1[i];
	n = 0;
	while (s2[n])
	{
		all_str[i] = s2[n];
		i++;
		n++;
	}
	all_str[i] = '\0';
	return (all_str);
}

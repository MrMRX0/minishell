/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 09:56:38 by ibougajd          #+#    #+#             */
/*   Updated: 2024/10/07 09:11:30 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	len_nbr(int n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n)
	{
		n /= 10;
		i++;
	}
	if (i == 0)
		return (1);
	return (i);
}

char	*ft_itoa(int n)
{
	char	*string;
	int		len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = len_nbr(n);
	string = ft_malloc((len + 1) * sizeof(char));
	if (!string)
		return (NULL);
	string[len] = '\0';
	if (n < 0)
	{
		string[0] = '-';
		n *= -1;
	}
	if (n == 0)
		string[0] = '0';
	while (n)
	{
		string[--len] = (n % 10) + ('0');
		n = n / 10;
	}
	return (string);
}

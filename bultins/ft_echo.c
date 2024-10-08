/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-bou <nait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:27:13 by nait-bou          #+#    #+#             */
/*   Updated: 2024/09/24 11:50:56 by nait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incld/minishell.h"

int	ft_strncmp_echo(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
	{
		i++;
		if (str[i] == '\0')
			return (1);
		while (str[i] == 'n')
			i++;
		if (str[i] == '\0')
			return (0);
	}
	return (1);
}

t_bool	ft_echo(char **av)
{
	int	i;
	int	option;

	i = 1;
	option = 0;
	if (nb_args(av) > 1)
	{
		while (av[i] && ft_strncmp_echo(av[i]) == 0)
		{
			option = 1;
			i++;
		}
		while (av[i])
		{
			ft_putstr_fd(av[i], 1);
			if (av[i + 1] && av[i][0] != '\0')
				write(1, " ", 1);
			i++;
		}
	}
	if (option == 0)
		write(1, "\n", 1);
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-bou <nait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:19:47 by nait-bou          #+#    #+#             */
/*   Updated: 2024/09/26 11:42:32 by nait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incld/minishell.h"

int	nb_count(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}

int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

void	ft_exit_helper(char **av, t_data *data)
{
	write(2, "exit\n", 5);
	write(2, "exit: numeric argument required\n", 33);
	data->exit_status = 2;
	free_close_all(data, av);
	exit(data->exit_status);
}

void	ft_exit_helper2(t_data *data, char **av)
{
	int	i;

	write(2, "exit\n", 5);
	i = ft_atoi(av[1]);
	if (ft_strlen(av[1]) > 19)
	{
		ft_putstr_fd("exit numeric argument required", 2);
		i = 2;
	}
	free_close_all(data, av);
	exit((unsigned char)i);
}

t_bool	ft_exit(char **av, t_data *data)
{

	if (nb_count(av) == 1 && data->flag == 1)
	{
		data->exit_status = 0;
		// free_close_all(data, av);
		exit(data->exit_status);
	}
	if (nb_count(av) == 1)
	{
		write(2, "exit\n", 5);
		// free_close_all(data, av);
		exit(data->exit_status);
	}
	if (nb_count(av) > 2)
	{
		write(2, "exit\n", 5);
		write(2, "exit: too many arguments\n", 25);
		data->exit_status = 1;
		return (false);
	}
	else if (ft_isnumber(av[1]) == false)
		ft_exit_helper(av, data);
	else
		ft_exit_helper2(data, av);
	return (true);
}

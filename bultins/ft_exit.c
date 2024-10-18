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
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

void	exit_case_2(char **av, t_data *data)
{
	if (nb_count(av) == 2 && !ft_isnumber(av[1]))
	{
		data->exit_status = 2;
		ft_error(data, av[0], ": numeric argument required\n",
			data->exit_status);
		ft_free_all();
		exit(data->exit_status);
	}
	else if (nb_count(av) > 2)
	{
		if (ft_isnumber(av[1]))
		{
			data->exit_status = 2;
			ft_error(data, av[0], ": too many arguments\n", data->exit_status);
		}
		else
		{
			data->exit_status = 2;
			ft_error(data, av[0], ": numeric argument required\n",
				data->exit_status);
			ft_free_all();
			exit(data->exit_status);
		}
	}
}

t_bool	ft_exit(char **av, t_data *data)
{
	int	i;

	i = 0;
	if (nb_count(av) == 1)
	{
		if (data->flag != 1)
			write(2, "exit\n", 5);
		data->exit_status = 0;
		ft_free_all();
		exit(data->exit_status);
	}
	if (nb_count(av) == 2 && ft_isnumber(av[1]))
	{
		i = ft_atoi(av[1]);
		if (ft_strlen(av[1]) > 19)
		{
			ft_putstr_fd("exit numeric argument required\n", 2);
			i = 2;
		}
		else
			ft_putstr_fd("exit\n", 2);
		ft_free_all();
		exit((unsigned char)i);
	}
	return (exit_case_2(av, data), true);
}

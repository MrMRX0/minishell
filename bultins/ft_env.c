/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-bou <nait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:37:52 by nait-bou          #+#    #+#             */
/*   Updated: 2024/09/24 10:26:50 by nait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_env(char **av, t_data *data)
{
	t_env	*tmp;

	tmp = data->env_list;
	if (nb_args(av) > 1)
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		return (false);
	}
	while (tmp)
	{
		ft_putstr_fd(tmp->key, 1);
		write(1, "=", 1);
		ft_putstr_fd(tmp->value, 1);
		write(1, "\n", 1);
		tmp = tmp->next;
	}
	return (true);
}
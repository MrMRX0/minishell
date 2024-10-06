/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-bou <nait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 09:53:10 by nait-bou          #+#    #+#             */
/*   Updated: 2024/09/24 10:24:10 by nait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incld/minishell.h"

void	remove_variable(char *key, t_data *data)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = data->env_list;
	prev = NULL;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			if (prev)
				prev->next = tmp->next;
			else
				data->env_list = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

t_bool	ft_unset(char **av, t_data *data)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (is_exported(av[i], data))
			remove_variable(av[i], data);
		i++;
	}
	return (true);
}
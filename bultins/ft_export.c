/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:59:33 by nait-bou          #+#    #+#             */
/*   Updated: 2024/10/07 11:10:05 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incld/minishell.h"

void	add_exported_variable(char *variable, t_data *data)
{
	t_env	*tmp;
	t_env	*new;
	char	*key;

	key = ft_key(variable);
	tmp = data->env_list;
	new = init_new_variable(variable, key);
	if (!new)
		return ;
	if (!tmp)
		data->env_list = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	update_exported_variable(char *variable, t_data *data)
{
	t_env	*tmp;
	char	*key;

	key = ft_key(variable);
	tmp = data->env_list;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
		{
			update_value(tmp, variable);
			break ;
		}
		tmp = tmp->next;
	}
}

t_bool	is_exported(char *variable, t_data *data)
{
	t_env	*tmp;
	char	*key;

	key = ft_key(variable);
	tmp = data->env_list;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
		{
			return (true);
		}
		tmp = tmp->next;
	}
	return (false);
}

t_bool	ft_export(char **av, t_data *data)
{
	int		i;
	t_env	*tmp;
	t_env	*tmp2;

	tmp2 = data->env_list;
	tmp = ft_copy_env(tmp2);
	ft_sort_env(tmp);
	i = 1;
	if (av[1] == NULL)
		print_env(tmp);
	else
	{
		while (av[i])
		{
			if (ft_export_check(av, i) == false)
				;
			else if (is_exported(av[i], data))
				update_exported_variable(av[i], data);
			else
				add_exported_variable(av[i], data);
			i++;
		}
	}
	return (true);
}

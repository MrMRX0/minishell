/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-bou <nait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:59:33 by nait-bou          #+#    #+#             */
/*   Updated: 2024/09/22 18:43:48 by nait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_global_tmp(t_env *tmp)
{
	t_env	*tmp2;

	while (tmp)
	{
		tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2->key);
		free(tmp2->value);
		free(tmp2);
	}
}

void	add_exported_variable(char *variable)
{
	t_env	*tmp;
	t_env	*new;
	char	*key;

	key = ft_key(variable);
	tmp = *get_env();
	new = init_new_variable(variable, key);
	if (!new)
		return ;
	if (!tmp)
        *get_env() = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	free(key);
}

void	update_exported_variable(char *variable)
{
	t_env	*tmp;
	char	*key;

	key = ft_key(variable);
	tmp = *get_env();
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
		{
			update_value(tmp, variable);
			break ;
		}
		tmp = tmp->next;
	}
	free(key);
}

t_bool	is_exported(char *variable)
{
	t_env	*tmp;
	char	*key;

	key = ft_key(variable);
	tmp = *get_env();
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
		{
			free(key);
			return (true);
		}
		tmp = tmp->next;
	}
	free(key);
	return (false);
}

t_bool	ft_export(char **av)
{
	int		i;
	t_env	*tmp;
    t_env    *tmp2;

    tmp2 = *get_env();
	tmp = ft_copy_env(tmp2);
	ft_sort_env(tmp);
	i = 1;
	if (!av[1])
		print_env(tmp);
	else
	{
		while (av[i])
		{
			if (ft_export_check(av, i) == false)
				;
			else if (is_exported(av[i]))
				update_exported_variable(av[i]);
			else
				add_exported_variable(av[i]);
			i++;
		}
	}
	return (free_global_tmp(tmp), true);
}



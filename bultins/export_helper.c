/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:36:15 by nait-bou          #+#    #+#             */
/*   Updated: 2024/10/06 01:50:30 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incld/minishell.h"

t_env	*ft_copy_env(t_env *env)
{
	t_env	*tmp;
	t_env	*new;
	t_env	*head;
	t_env	*prev;

	tmp = env;
	head = NULL;
	prev = NULL;
	new = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "_") != 0)
		{
			new = set_node(tmp);
			if (prev)
				prev->next = new;
			else
				head = new;
			prev = new;
		}
		tmp = tmp->next;
	}
	return (head);
}

void	ft_sort_env(t_env *env)
{
	t_env	*tmp;
	t_env	*tmp2;

	tmp = env;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (ft_strcmp(tmp->key, tmp2->key) > 0)
			{
				swap_env(tmp, tmp2);
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}

void	print_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strlen(tmp->value) == 0)
		{
			if (tmp->q)
				printf("declare -x %s=\"\"\n", tmp->key);
			else
				printf("declare -x %s\n", tmp->key);
		}
		else
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

t_bool	ft_export_check(char **av, int i)
{
	int	d;

	d = 0;
	if (!is_valid_identifier(av[i][d], 0))
	{
		printf("export: `%s': not a valid identifier\n", av[i]);
		return (false);
	}
	d++;
	while (av[i][d] && av[i][d] != '=' && !(av[i][d] == '+' && av[i][d
			+ 1] == '='))
	{
		if (!is_valid_identifier(av[i][d], d))
			return (printf("export: `%s': not a valid identifier\n", av[i]),
				false);
		d++;
	}
	return (true);
}

t_bool	is_valid_identifier(char c, int i)
{
	if (i == 0)
	{
		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
			return (true);
	}
	else
	{
		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
			|| (c >= '0' && c <= '9') || c == '_')
			return (true);
	}
	return (false);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-bou <nait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:36:15 by nait-bou          #+#    #+#             */
/*   Updated: 2024/09/23 11:26:12 by nait-bou         ###   ########.fr       */
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
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "_") != 0)
		{
			new = (t_env *)malloc(sizeof(t_env));
			new->key = ft_strdup(tmp->key);
			new->value = ft_strdup(tmp->value);
			new->q = tmp->q;
			new->next = NULL;
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
	char	*key;
	char	*value;

	tmp = env;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (ft_strcmp(tmp->key, tmp2->key) > 0)
			{
				key = tmp->key;
				value = tmp->value;
				tmp->key = tmp2->key;
				tmp->value = tmp2->value;
				tmp2->key = key;
				tmp2->value = value;
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
			if(tmp->q == 1)
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
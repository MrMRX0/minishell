/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buil_tools1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-bou <nait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:54:28 by nait-bou          #+#    #+#             */
/*   Updated: 2024/09/25 11:55:29 by nait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incld/minishell.h"

void	change_pwd(t_env *envs, const char *old_pwd, const char *pwd)
{
	set_env(envs, "OLDPWD", old_pwd);
	set_env(envs, "PWD", pwd);
}

t_env	*set_node(t_env *tmp)
{
	t_env	*new;

	new = (t_env *)ft_malloc(sizeof(t_env));
	new->key = ft_strdup(tmp->key);
	new->value = ft_strdup(tmp->value);
	new->q = tmp->q;
	new->next = NULL;
	return (new);
}

void	swap_env(t_env *tmp, t_env *tmp2)
{
	char	*key;
	char	*value;
	int		q;

	key = tmp->key;
	value = tmp->value;
	q = tmp->q;
	tmp->key = tmp2->key;
	tmp->value = tmp2->value;
	tmp->q = tmp2->q;
	tmp2->key = key;
	tmp2->value = value;
	tmp2->q = q;
}

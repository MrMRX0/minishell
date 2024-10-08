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

void	set_node(t_env *new, t_env *tmp)
{
	new = (t_env *)ft_malloc(sizeof(t_env));
	new->key = ft_strdup(tmp->key);
	new->value = ft_strdup(tmp->value);
	new->q = tmp->q;
	new->next = NULL;
}

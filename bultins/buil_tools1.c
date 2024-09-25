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

#include "../minishell.h"

void	change_pwd(t_env *envs, const char *old_pwd, const char *pwd, t_data *data)
{
	set_env(envs, "OLDPWD", old_pwd, data);
	set_env(envs, "PWD", pwd, data);
}
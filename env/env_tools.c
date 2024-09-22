/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-bou <nait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 22:20:45 by nait-bou          #+#    #+#             */
/*   Updated: 2024/09/22 16:47:41 by nait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env **get_env(void)
{
	static t_env *env_list = NULL;
	return (&env_list);
}

void billed_env_list(char **env, t_data *data)
{

	data->env_list = get_env();
	data->env_list = init_env(env);
	shlvl_init(data);
}


void	shlvl_init(t_data *data)
{
	t_env	*tmp;
	char	*shlvl;

	tmp = data->env_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "SHLVL") == 0)
		{
			if (ft_strcmp(tmp->value, "999") == 0)
			{
				free(tmp->value);
				printf("warning: shell level (999) too high, resetting to 1\n");
				tmp->value = ft_strdup("1");
				return ;
			}
			shlvl = ft_itoa(ft_atoi(tmp->value) + 1);
			free(tmp->value);
			tmp->value = ft_strdup(shlvl);
			free(shlvl);
			return ;
		}
		tmp = tmp->next;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-bou <nait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 22:20:45 by nait-bou          #+#    #+#             */
/*   Updated: 2024/09/24 09:37:18 by nait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incld/minishell.h"



void billed_env_list(char **env, t_data *data)
{

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

char	**transform_env(t_env *env)
{
	t_env	*tmp;
	char	**envp;
	int		i;
	char	*str;

	i = 0;
	tmp = env;
	envp = NULL;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	envp = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	tmp = env;
	str = NULL;
	while (tmp)
	{
		join_key_value(str, envp, i, tmp);
		i++;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}

void	join_key_value(char *str, char **envp, int i, t_env *tmp)
{
	char *to_free;

	to_free = NULL;
	if (str != NULL)
		free(str);
	str = ft_strdup(tmp->key);
	to_free = str;
	envp[i] = ft_strjoin(str, "=");
	free(to_free);
	to_free = envp[i];
	envp[i] = ft_strjoin(envp[i], tmp->value);
	free(to_free);
}
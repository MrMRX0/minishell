/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buil_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-bou <nait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:06:27 by nait-bou          #+#    #+#             */
/*   Updated: 2024/09/24 10:26:36 by nait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_key(char *variable)
{
	char	*key;
	int		i;

	i = 0;
	while (variable[i] && variable[i] != '=' && !(variable[i] == '+'
			&& variable[i + 1] == '='))
		i++;
	key = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (variable[i] && variable[i] != '=' && !(variable[i] == '+'
			&& variable[i + 1] == '='))
	{
		key[i] = variable[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

void	update_value(t_env *tmp, char *variable)
{
	char	*new_value;

	if (ft_strchr(variable, '=') == NULL)
		return ;
	if (ft_strstr(variable, "+=") == NULL)
	{
		free(tmp->value);
		tmp->value = ft_strdup(ft_strchr(variable, '=') + 1);
	}
	else
	{
		new_value = malloc(ft_strlen(tmp->value) + ft_strlen(
					ft_strchr(variable, '=') + 1) + 1);
		if (!new_value)
			return ;
		ft_strcpy(new_value, tmp->value);
		ft_strcat(new_value, ft_strchr(variable, '=') + 1);
		free(tmp->value);
		tmp->value = new_value;
	}
}

t_env	*init_new_variable(char *variable, char *key)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	if (ft_strstr(variable, "+=") == NULL)
	{
		if (ft_strchr(variable, '=') == NULL)
			new->value = ft_strdup("");
		else
			new->value = ft_strdup(ft_strchr(variable, '=') + 1);
	}
	else
	{
		if (ft_strchr(variable, '=') == NULL)
			new->value = ft_strdup("");
		else
			new->value = ft_strdup(ft_strchr(variable, '=') + 1);
	}
	new->next = NULL;
	return (new);
}

int	nb_args(char **args)
{
	int	len;

	len = 0;
	while (args[len])
		len++;
	return (len);
}
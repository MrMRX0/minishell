/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buil_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:06:27 by nait-bou          #+#    #+#             */
/*   Updated: 2024/10/07 08:52:14 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incld/minishell.h"

char	*ft_key(char *variable)
{
	char	*key;
	int		i;

	i = 0;
	while (variable[i] && variable[i] != '=' && !(variable[i] == '+'
			&& variable[i + 1] == '='))
		i++;
	key = (char *)ft_malloc(sizeof(char) * (i + 1));
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
		tmp->value = ft_strdup(ft_strchr(variable, '=') + 1);
	}
	else
	{
		new_value = ft_malloc(ft_strlen(tmp->value) + ft_strlen(
					ft_strchr(variable, '=') + 1) + 1);
		if (!new_value)
			return ;
		ft_strcpy(new_value, tmp->value);
		ft_strcat(new_value, ft_strchr(variable, '=') + 1);
		tmp->value = new_value;
	}
}

t_env	*init_new_variable(char *var, char *key)
{
	t_env	*new;
	char	*equal;

	new = (t_env *)ft_malloc(sizeof(t_env));
	new->key = ft_strdup(key);
	equal = ft_strchr(var, '=');
	new->q = (equal != NULL);
	if (ft_strstr(var, "+=") == NULL)
	{
		if (equal == NULL)
			new->value = ft_strdup("");
		else
			new->value = ft_strdup(equal + 1);
	}
	else
	{
		if (equal == NULL)
			new->value = ft_strdup("");
		else
			new->value = ft_strdup(equal + 1);
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

void	error(const char *cmd, const char *msg)
{
	if (msg && cmd)
		printf("%s: %s\n", cmd, msg);
}

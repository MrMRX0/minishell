/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 22:18:42 by nait-bou          #+#    #+#             */
/*   Updated: 2024/10/07 11:14:38 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incld/minishell.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*copy;
	size_t	i;

	copy = (char *)ft_malloc((n + 1) * sizeof(char));
	i = 0;
	while (i < n && s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

t_env	*create_env_node(const char *env_var)
{
	t_env	*new_node;
	char	*delimiter;

	new_node = (t_env *)ft_malloc(sizeof(t_env));
	delimiter = ft_strchr(env_var, '=');
	if (delimiter != NULL)
		new_node->q = 1;
	else
		new_node->q = 0;
	new_node->key = ft_strndup(env_var, delimiter - env_var);
	new_node->value = ft_strdup(delimiter + 1);
	new_node->next = NULL;
	return (new_node);
}

char	**ft_null_env(void)
{
	char	**default_env;
	char	cwd[PATH_MAX];
	char	*pwd;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (NULL);
	default_env = (char **)ft_malloc(sizeof(char *) * 4);
	if (!default_env)
		return (NULL);
	pwd = (char *)ft_malloc(ft_strlen("PWD=") + ft_strlen(cwd) + 1);
	if (!pwd)
		return (NULL);
	ft_strcpy(pwd, "PWD=");
	ft_strcat(pwd, cwd);
	default_env[0] = pwd;
	default_env[1] = ft_strdup("SHLVL=1");
	default_env[2] = ft_strdup("_=/usr/bin/env");
	default_env[3] = NULL;
	if (!default_env[1] || !default_env[2])
		return (NULL);
	return (default_env);
}

t_env	*init_env(char **env)
{
	t_env	*head;
	t_env	*current;
	t_env	*new_node;

	if (env[0] == NULL)
		env = ft_null_env();
	head = NULL;
	current = NULL;
	while (*env)
	{
		new_node = create_env_node(*env);
		if (!head)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
		env++;
	}
	return (head);
}

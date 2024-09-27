/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-bou <nait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:44:35 by nait-bou          #+#    #+#             */
/*   Updated: 2024/09/26 10:24:40 by nait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_value(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	set_env(t_env *env, const char *key, const char *value, t_data *data)
{
	t_env	*new_env;

	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			free(env->value);
			env->value = ft_strdup(value);
			return ;
		}
		env = env->next;
	}
	new_env = (t_env *)malloc(sizeof(t_env));
	new_env->key = ft_strdup(key);
	new_env->value = ft_strdup(value);
	new_env->next = data->env_list;
	data->env_list = new_env;
}

t_bool	check_directory(char *dir)
{
	struct stat	info; 

	if (access(dir, F_OK) == -1)
		return (error("cd", "No such file or directory"), false);
	if (stat(dir, &info) == -1)
		return (error("cd", "Error!"), false);
	if (!S_ISDIR(info.st_mode))
		return (error("cd", "Not a directory"), false);
	if (access(dir, R_OK | X_OK) == -1)
		return (error("cd", "Permission denied"), false);
	return (true);
}

t_bool	check_cd(char **av, char *old_pwd)
{
	if (av[1] != NULL)
	{
		if (av[2])
			return (error("cd", "too many arguments"), false);
		if (!getcwd(old_pwd, PATH_MAX))
			return (error("cd", "getcwd failed"), false);
	}
	return (true);
}

t_bool	ft_cd(char **av, t_data *data)
{
	char	old_pwd[PATH_MAX];
	char	new_pwd[PATH_MAX];
	char	*home;

	if (check_cd(av, old_pwd) == false)
		return (false);
	if (!av[1])
	{
		home = get_env_value(data->env_list, "HOME");
		if (!home)
			return (error("cd", "HOME not set"), false);
		ft_strcpy(new_pwd, home);
		return (1);
	}
	else
	{
		ft_strcpy(new_pwd, av[1]);
		if (!check_directory(new_pwd))
			return (false);
	}
	if (chdir(new_pwd) == -1)
		return (error("cd", new_pwd), false);
	if (!getcwd(new_pwd, PATH_MAX))
		return (error("cd", "getcwd failed"), false);
	return (change_pwd(data->env_list, old_pwd, new_pwd, data), 1);
}
 
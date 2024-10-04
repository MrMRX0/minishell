/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 04:21:54 by ibougajd          #+#    #+#             */
/*   Updated: 2024/10/02 06:15:31 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *check_splited_path(char **splited_path, char *command)
{
	int i;
	char *path;
	char *to_free;

	i = 0;
	to_free = NULL;
	while(splited_path[i])
	{
		path = ft_strjoin(splited_path[i], "/");
		to_free = path;
		path = ft_strjoin(path, command);
		free(to_free);
		if((access(path, X_OK) == 0))
			return(path);
		free(path);
		i++;
	}
	return(NULL);
}
char *check_path(char *command, t_data *data)
{
	char *path;
	char **splited_path;
	int i;
	int j;

	i = 0;
	j = 0;
	path = NULL;
	splited_path = NULL;
	while(data->env[i])
	{
		splited_path = ft_split(data->env[i], '=');
		if(strcmp(splited_path[0], "PATH") == 0)
		{
			free(splited_path[0]);
			free(splited_path[1]);
			free(splited_path);
			break;
		}
		while(splited_path[j])
		{
			free(splited_path[j]);
			j++;
		}
		j = 0;
		free(splited_path);
		i++;
	}
	if(!data->env[i])
		return(NULL);
	path = data->env[i];
	splited_path = ft_split(path, ':');
	i = 0;
	path = check_splited_path(splited_path, command);
	j = 0;
	while(splited_path[j])
	{
		free(splited_path[j]);
		j++;
	}
	free(splited_path);
	return(path);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 04:21:54 by ibougajd          #+#    #+#             */
/*   Updated: 2024/10/01 04:21:56 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_splited_path(char **splited_path, char *command)
{
	int i;
	char *path;
	char slash[2];

	i = 0;
	slash[0] = '/';
	slash[1] = '\0';
	while(splited_path[i])
	{
		path = ft_strjoin(splited_path[i], slash);
		path = ft_strjoin(path, command);
		if((access(path, X_OK) == 0))
			return(1);
		i++;
	}
	return(0);
}
int check_path(char *command, t_data *data)
{
	char *path;
	char **splited_path;
	int i;

	i = 0;
	path = NULL;
	splited_path = NULL;
	while(data->env[i])
	{
		splited_path = ft_split(data->env[i], '=');
		if(strcmp(splited_path[0], "PATH") == 0)
			break;
		i++;
	}
	if(!data->env[i])
		return(0);
	path = data->env[i];
	free(splited_path[0]);
	free(splited_path[1]);
	free(splited_path);
	splited_path = ft_split(path, ':');
	i = 0;
	i = check_splited_path(splited_path, command);
	return(i);
}
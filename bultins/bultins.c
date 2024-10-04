/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultins.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 04:22:59 by ibougajd          #+#    #+#             */
/*   Updated: 2024/10/04 20:56:21 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incld/minishell.h"

void	bultins_runner(char **av, t_data *data)
{
	if (ft_strcmp(av[0], "env") == 0)
		ft_env(av, data);
	else if (ft_strcmp(av[0], "export") == 0)
		ft_export(av, data);
	else if (ft_strcmp(av[0], "unset") == 0)
		ft_unset(av, data);
	else if (ft_strcmp(av[0], "pwd") == 0)
		ft_pwd(av);
	else if (ft_strcmp(av[0], "echo") == 0)
		ft_echo(av);
	else if (ft_strcmp(av[0], "cd") == 0)
		ft_cd(av, data);
	else if (ft_strcmp(av[0], "exit") == 0)
		ft_exit(av, data);
}

int 	ft_buitin_check(char **av)
{
	if (ft_strcmp(av[0], "echo") == 0)
		return (0);
	else if (ft_strcmp(av[0], "pwd") == 0)
		return (0);
	else if (ft_strcmp(av[0], "exit") == 0)
		return (0);
	else if (ft_strcmp(av[0], "env") == 0)
		return (0);
	else if (ft_strcmp(av[0], "export") == 0)
		return (0);
	else if (ft_strcmp(av[0], "unset") == 0)
		return (0);
	else if (ft_strcmp(av[0], "cd") == 0)
		return (0);
	return (1);
}
int bultins(char **args, t_data *data)
{
	int i;

	i = 0;
	if (ft_buitin_check(args) == 0)
	{
		bultins_runner(args,data);
		while(args[i])
		{
			free(args[i]);
			i++;
		}
		free(args);
		return 1;
	}
	return(0);
}
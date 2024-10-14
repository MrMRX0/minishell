/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultins.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 04:22:59 by ibougajd          #+#    #+#             */
/*   Updated: 2024/10/07 11:26:02 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incld/minishell.h"

t_bool	bultins_runner(char **av, t_data *data)
{
	if (ft_strcmp(av[0], "env") == 0)
		return (ft_env(av, data));
	else if (ft_strcmp(av[0], "export") == 0)
		return (ft_export(av, data));
	else if (ft_strcmp(av[0], "unset") == 0)
		return (ft_unset(av, data));
	else if (ft_strcmp(av[0], "pwd") == 0)
		return (ft_pwd(av));
	else if (ft_strcmp(av[0], "echo") == 0)
		return (ft_echo(av));
	else if (ft_strcmp(av[0], "cd") == 0)
		return (ft_cd(av));
	else if (ft_strcmp(av[0], "exit") == 0)
		return (ft_exit(av, data));
	return (false);
}

int	ft_buitin_check(char **av)
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

int	bultins(char **args, t_data *data)
{
	if (ft_buitin_check(args) == 0)
	{
		if (bultins_runner(args, data) == true)
			g_global_data->exit_status = 0;
		else
			g_global_data->exit_status = 1;
		return (1);
	}
	return (0);
}

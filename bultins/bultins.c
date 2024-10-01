/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultins.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 04:22:59 by ibougajd          #+#    #+#             */
/*   Updated: 2024/10/01 04:31:55 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	bultins_runner(char **av, t_data *data)
{
	if (ft_strncmp(av[0], "env", 3) == 0)
		ft_env(av, data);
	else if (ft_strncmp(av[0], "export", 6) == 0)
		ft_export(av, data);
	else if (ft_strncmp(av[0], "unset", 5) == 0)
		ft_unset(av, data);
	else if (ft_strncmp(av[0], "pwd", 3) == 0)
		ft_pwd(av);
	else if (ft_strncmp(av[0], "echo", 4) == 0)
		ft_echo(av);
	else if (ft_strncmp(av[0], "cd", 2) == 0)
		ft_cd(av, data);
	else if (ft_strncmp(av[0], "exit", 4) == 0)
		ft_exit(av, data);
}

int 	ft_buitin_check(char **av)
{
	if (ft_strncmp(av[0], "echo", 4) == 0)
		return (0);
	else if (ft_strncmp(av[0], "pwd", 3) == 0)
		return (0);
	else if (ft_strncmp(av[0], "exit", 4) == 0)
		return (0);
	else if (ft_strncmp(av[0], "env", 3) == 0)
		return (0);
	else if (ft_strncmp(av[0], "export", 6) == 0)
		return (0);
	else if (ft_strncmp(av[0], "unset", 6) == 0)
		return (0);
	else if (ft_strncmp(av[0], "cd", 2) == 0)
		return (0);
	return (1);
}
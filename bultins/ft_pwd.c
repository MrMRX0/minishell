/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:30:16 by nait-bou          #+#    #+#             */
/*   Updated: 2024/10/04 20:56:21 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incld/minishell.h"

t_bool	ft_pwd(char **av)
{
	char	pwd[PATH_MAX];

	if (nb_args(av) > 1)
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		return (false);
	}
	getcwd(pwd, PATH_MAX);
	ft_putstr_fd(pwd, 1);
	write(1, "\n", 1);
	return (true);
}
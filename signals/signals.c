/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:55:16 by nait-bou          #+#    #+#             */
/*   Updated: 2024/10/08 10:14:50 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incld/minishell.h"

void	handler(int signum)
{
	(void)signum;
	g_global_data->exit_status = 130;
	if (g_global_data->sig_flag2 != 22)
		write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handler_2(int signum)
{
	(void)signum;
	g_global_data->exit_status = 130;
	if (g_global_data->sig_flag3 == 1)
		write(1, "\n", 1);
	g_global_data->sig_flag3 = 0;
}

void	handler_3(int signum)
{
	(void)signum;
	g_global_data->exit_status = 131;
	if (g_global_data->sig_flag3 == 1)
		write(1, "\n", 1);
}

void	signal_handler_heredoc(void)
{
	signal(SIGINT, handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	handler_heredoc(int signum)
{
	g_global_data->sig_flag = 1;
	g_global_data->exit_status = 130;
	close(0);
	(void)signum;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_global_data->sig_flag2 = 22;
}

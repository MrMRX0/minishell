/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-bou <nait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:55:16 by nait-bou          #+#    #+#             */
/*   Updated: 2024/09/30 12:43:56 by nait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incld/minishell.h"

void    main_signal_handler(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}

void    handler(int signum)
{
	(void)signum;
	global_data->exit_status = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}



void	handler_2(int signum)
{
	(void)signum;
	global_data->exit_status = 130;
	write(1, "\n", 1);
}

void	handler_3(int signum)
{
	(void)signum;
	global_data->exit_status = 131;
	write(1, "\n", 1);
}

void	signal_handler_heredoc(void)
{
	signal(SIGINT, handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	handler_heredoc(int signum)
{
	write(1, "\n", 1);
	global_data->sig_flag = 1;
	global_data->exit_status = 130;
	close(0);
	(void)signum;
}
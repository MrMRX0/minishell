/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:55:16 by nait-bou          #+#    #+#             */
/*   Updated: 2024/10/04 20:56:21 by ibougajd         ###   ########.fr       */
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
    if (signum == SIGINT)
    {
        write(1, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

// void   middle_exec_signal(t_data *data)
// {
//     struct sigaction sa;
//     sa.sa_flags = SA_SIGINFO;
//     sa.sa_sigaction = exec_handler;
//     sigaction(SIGINT, &sa, (void *)data);
//     sigaction(SIGQUIT, &sa, (void *)data);
// }

void    exec_handler(int signum)
{
    if (signum == SIGINT)
    {
        write(1, "\n", 1);

    }
    else if (signum == SIGQUIT)
    {
        write(1, "\n", 1);

    }
}

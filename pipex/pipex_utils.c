/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 18:35:08 by ibougajd          #+#    #+#             */
/*   Updated: 2024/10/07 10:13:51 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incld/minishell.h"

void	close_fds(int n, int *fd)
{
	int	i;

	i = 0;
	while (i < 2 * n)
	{
		close(fd[i]);
		i++;
	}
}

char	**get_command(t_data *data, int *std_in, int *std_out)
{
	t_token	*pipe_token;
	char	**command;

	command = NULL;
	pipe_token = extract_token(&data->token);
	command = get_copy_of_token_v1(command, &pipe_token);
	expand(command, data, &pipe_token);
	join_nodes(&pipe_token);
	*std_in = redirect_input(&pipe_token, data);
	*std_out = redirections(&pipe_token, data);
	if (*std_in == -1 || *std_out == -1)
		return (NULL);
	command = get_copy_of_token_v2(command, &pipe_token);
	return (command);
}

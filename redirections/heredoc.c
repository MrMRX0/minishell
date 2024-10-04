/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:25:23 by ibougajd          #+#    #+#             */
/*   Updated: 2024/10/04 21:48:41 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incld/minishell.h"

void	set_heredoc_input_value(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	if (!tmp)
		return ;
	while (tmp)
	{
		if (tmp->type == HERDOK && tmp->next)
			tmp->next->type = HERDOK_INPUT;
		tmp = tmp->next;
	}
}

char	*get_file_name(void)
{
	static int	i;
	char		s2[2];
	char		*file_path;

	s2[0] = (i + 48);
	s2[1] = '\0';
	file_path = "/tmp/heardok";
	file_path = ft_strjoin(file_path, s2);
	i++;
	return (file_path);
}

void	open_heredoc(t_data *data, t_token **node, int fd, char *input)
{
	while (1)
	{
		input = readline(">");
		if (!input)
		{
			restore_stdin_stdout(data->std_in, data->std_in);
			save_stdin_stdout(&data->std_in, &data->std_in);
			printf(HEREDOC_ERROR, data->prompt_call_times, (*node)->next->arg);
			break ;
		}
		if (ft_strcmp(input, (*node)->next->arg) == 0)
			break ;
		if ((ft_strchr(input, '$')) && (ft_strchr((*node)->next->arg,
					'\'') == 0) && (ft_strchr((*node)->next->arg, '\"') == 0))
			input = expander(input, data);
		if (input)
			write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
	}
	free(input);
}

int	heredoc(t_token **node, t_data *data)
{
	char	*filepath;
	int		fd;
	char	*input;

	if (!(*node)->next)
		return (-1);
	input = NULL;
	filepath = get_file_name();
	fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (access(filepath, R_OK) == -1)
		return (ft_error(data, filepath, P_D, 1), -1);
	open_heredoc(data, node, fd, input);
	close(fd);
	fd = open(filepath, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Failed to reopen file\n", 22);
		return (-1);
	}
	free(filepath);
	return (fd);
}

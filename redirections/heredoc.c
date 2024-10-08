/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:25:23 by ibougajd          #+#    #+#             */
/*   Updated: 2024/10/08 19:19:38 by ibougajd         ###   ########.fr       */
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

t_bool	open_heredoc(t_data *data, t_token **node, int fd, char *end)
{
	char	*input;

	input = NULL;
	while (1)
	{
		signal_handler_heredoc();
		g_global_data->tmp_heredoc_flag = 1;
		input = readline(">");
		if (!input)
		{
			if (g_global_data->sig_flag == 1)
				return (write(1, "\n", 1), false);
			restore_stdin_stdout(data->std_in, data->std_in);
			save_stdin_stdout(&data->std_in, &data->std_in);
			printf(HEREDOC_ERROR, data->prompt_call_times, (*node)->next->arg);
			break ;
		}
		if (ft_strcmp(input, end) == 0)
			break ;
		if ((ft_strchr(input, '$')) && (data->expand_flag == 0))
			input = expander(input, data);
		if (input && write(fd, input, ft_strlen(input)))
			write(fd, "\n", 1);
	}
	return (true);
}

char	*remove_qoutes(char *input, t_data *data)
{
	char	*new;
	int		len;
	int		i;

	i = 0;
	len = 0;
	new = NULL;
	while (input[i])
	{
		if (input[i] != '\'' && input[i] != '\"')
			len++;
		i++;
	}
	new = ft_malloc((len + 1) * sizeof(char));
	i = 0;
	len = 0;
	while (input[i])
	{
		if (++i && input[i] != '\'' && input[i] != '\"')
		{
			new[len] = input[i];
			len++;
		}
	}
	return (new[len] = '\0', data->expand_flag = 1, new);
}

int	heredoc(t_token **node, t_data *data)
{
	char	*filepath;
	int		fd;
	char	*input;

	if (!(*node)->next)
		return (-1);
	input = (*node)->next->arg;
	filepath = get_file_name();
	fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (access(filepath, R_OK) == -1)
		return (ft_error(data, filepath, P_D, 1), -1);
	data->expand_flag = 0;
	if (ft_strcmp(input, "\"\"") == 0)
		input = ft_strdup("\0");
	else if (ft_strchr(input, '\'') || ft_strchr(input, '\"'))
		input = remove_qoutes(input, data);
	if (open_heredoc(data, node, fd, input) == false)
		return (-1);
	close(fd);
	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		return (write(2, "Failed to reopen file\n", 22), -1);
	return (fd);
}

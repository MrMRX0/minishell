#include "minishell.h"

void set_heredoc_input_value(t_token **token)
{
	t_token *tmp;

	tmp = *token;
	if(!tmp)
		return ;
	while(tmp)
	{
		if(tmp->type == HERDOK && tmp->next)
			tmp->next->type = HERDOK_INPUT;
		tmp = tmp->next;
	}
}

int	heredoc(t_token **node, t_data *data)
{
	static int	i;
	char		s2[2];
	char		*filepath;
	int			fd;
	char		*input;
	char		*arg;

	if (!(*node)->next)
		return (-1);
	s2[0] = (i + 48);
	s2[1] = '\0';
	filepath = "/tmp/heardok";
	filepath = ft_strjoin(filepath, s2);
	i++;
	fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		write(2, "Failed to open file\n", 20); // Write to stderr if open fails
		return (-1);
	}
	free(filepath);
	input = NULL;
	arg = extraxt_arg((*node)->next->arg);
	while (1)
	{
		input = readline(">");
		if (!input)
		{
			printf("minishell: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n",
				data->prompt_call_times, (*node)->next->arg);
			break ;
		}
		if (ft_strcmp(input, arg) == 0)
			break ;
		if ((ft_strchr(input, '$')) && (ft_strchr((*node)->next->arg,
					'\'') == 0) && (ft_strchr((*node)->next->arg, '\"') == 0))
			input = herdok_expand(input, data);
		if (input)
			write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
	}
	close(fd);
	free(input);
	free(arg);
	fd = open(filepath, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Failed to reopen file\n", 22);
		return (-1);
	}
	return (fd);
}

char	*herdok_expand(char *str, t_data *data)
{
	int b;
	char *returned_str;
	char *final_str;
	char tmp[2];

	b = 0;
	final_str = NULL;
	returned_str = NULL;
	while (str[b])
	{
		if (str[b] == '$')
		{
			b++;
			returned_str = handle_dollar_sign(str + b, data, &b);
			if (returned_str)
				final_str = ft_strjoin(final_str, returned_str);
		}
		else
		{
			tmp[0] = str[b];
			tmp[1] = '\0';
			final_str = ft_strjoin(final_str, tmp);
			b++;
		}
	}
	return (final_str);
}
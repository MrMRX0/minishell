/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:49:01 by ibougajd          #+#    #+#             */
/*   Updated: 2024/09/26 17:52:57 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void join_nodes(t_token **token)
{
	t_token *tmp = *token;
	t_token *to_free;
	while(tmp)
	{
		if (tmp->next_command == 1 && !tmp->next)
			return;
		if(tmp->next_command == 1 && tmp->next)
		{
			tmp->arg = ft_strjoin(tmp->arg, tmp->next->arg);
			to_free = tmp->next;
			if(to_free->next)
				tmp->next = to_free->next;
			else
				tmp->next = NULL;
			tmp->type = 0;
			if(to_free->next_command == 0)
				tmp->next_command = 0;
			free(to_free);
		}
		if (tmp->next_command == 0)
			tmp = tmp->next;
	}
}
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
void	normal_execution(t_data *data)
{
	char **command;
	int red_fd = 0;
	int red_in = 0;

	command = NULL;
	set_heredoc_input_value(&data->token);
	command = get_copy_of_token(command, &(data->token));
	if(!command)
		return ;
	expand(command,data, &data->token);
	join_nodes(&data->token);
	red_fd = redirections(&data->token);
	red_in = redirect_input(&data->token, data);
	if(red_in == -1)
		return;
	if (red_fd)
		dup2(red_fd, STDOUT_FILENO);
	command = get_copy_of_token_v3(command, &(data->token));
	if(!command)
		return;
	execute(command, data);
}
t_token *extract_token(t_token **token)
{
	t_token *new;
	t_token *tmp;

	new = NULL;
	tmp = NULL;
	while((*token) && (*token)->type != PIPE)
	{
		
		ft_lst_add(&new);
		tmp = new;	
		while(tmp->next)
			tmp = tmp->next;
		tmp->arg = (*token)->arg;
		tmp->next_command = (*token)->next_command;
		tmp->type = (*token)->type;
		*token = (*token)->next;
	}
	if(*token)
		*token=(*token)->next;
	return(new);
}

void execution(t_data *data)
{
	int		i;
	
	i = get_size_of_tree(&data->token);
	if (!i)
		normal_execution(data);
	else
		pipe_pipe(i, data);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:49:01 by ibougajd          #+#    #+#             */
/*   Updated: 2024/09/25 12:41:14 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void join_nodes(t_token **token)
{
	t_token *tmp = *token;
	t_token *to_free;
	while(tmp)
	{
		if(tmp->next_command == 1 && tmp->next)
		{
			tmp->arg = ft_strjoin(tmp->arg, tmp->next->arg);
			to_free = tmp->next;
			if(to_free->next)
				tmp->next = to_free->next;
			else
				tmp->next = NULL;
			if(to_free->next_command == 0)
				tmp->next_command = 0;
			free(to_free);
		}
		// printf("%s\n", tmp->arg);
		// printf("%d\n", tmp->next_command);
		if (tmp->next_command == 0)
			tmp = tmp->next;
		// printf("arg=%s\n", tmp->arg);
	}
}
void	normal_execution(t_data *data)
{
	char **command;

	command = NULL;
	command = get_copy_of_token(command, &(data->token));
	
	if(data->lexer.dollar)
		expand(command,data->env, &data->token);
	join_nodes(&data->token);
	if (data->lexer.redirect_output)
		redirections(&data->token);
	if (data->lexer.redirect_input)
		redirect_input(&data->token);
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
	// ls -la | echo hello world | wc -l 
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
	//skip pipe
	if(*token)
		*token=(*token)->next;
	return(new);
}

void	pipe_execution(int i, t_data *data)
{
	int		j;
	char	***tree;
	t_token *pipe_token;
	char **command = NULL;
	
	tree = NULL;
	j = 0;
	pipe_token = NULL;
	tree = malloc((i + 1) * sizeof(char **));
	while(j <= i)
	{
		
		pipe_token  = extract_token(&data->token);
		command = get_copy_of_token(command, &pipe_token);
		expand(command,data->env, &pipe_token);
		redirections(&pipe_token);
		redirect_input(&pipe_token);
		tree[j] = get_copy_of_token_v3(tree[j], &pipe_token);
		j++;
	}
	pipe_pipe(tree, i, data);
}

void execution(t_data *data)
{
	int		i;
	
	i = get_size_of_tree(&data->token);
	if (!i)
		normal_execution(data);
	else
		pipe_execution(i, data);
}
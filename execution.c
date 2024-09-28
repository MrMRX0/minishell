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

void	normal_execution(t_data *data)
{
	char **command;
	int red_fd = 0;

	command = NULL;
	command = get_copy_of_token(command, &(data->token));
	
	if(data->lexer.dollar)
		expand(command,data->env, &data->token);
	if (data->lexer.redirect_output)
		red_fd = redirections(&data->token);
	if (data->lexer.redirect_input)
		redirect_input(&data->token);
	if (red_fd)
		dup2(red_fd, STDOUT_FILENO);
	join_nodes(&data->token);
	// while(data->token)
	// {
	// 	printf("%s ",data->token->arg);
	// 	printf("%d ",data->token->type);
	// 	printf("%d \n",data->token->next_command);
	// 	data->token = data->token->next;
	// }
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
// void ft_lst_add_2(t_hold_token **lst, t_token ** token) 
// {
// 	if (!*lst) {
// 		*lst = malloc(sizeof(t_hold_token));
// 		if (!*lst) {
// 			perror("malloc failed");
// 			exit(EXIT_FAILURE);
// 		}
// 		(*lst)->next = NULL;
// 		(*lst)->token = *token;
// 		return;
// 	}
// 	t_hold_token *current = *lst;
// 	while (current->next)
// 		current = current->next;
// 	t_hold_token *new_node = malloc(sizeof(t_hold_token));
// 	if (!new_node)
// 	{
// 		perror("malloc failed");
// 		exit(EXIT_FAILURE);
// 	}
// 	new_node->next = NULL;
// 	new_node->token = *token;
// 	current->next = new_node;
// }
void	pipe_execution(int i, t_data *data)
{
	pipe_pipe(i, data);
	// int		j;
	// char	***tree;
	// t_token *pipe_token;
	// t_hold_token *holder = NULL;
	// char **command = NULL;
	
	// tree = NULL;
	// j = 0;
	// pipe_token = NULL;
	// tree = malloc((i + 1) * sizeof(char **));
	// while(j <= i)
	// {
		
	// 	ft_lst_add_2(&holder, &pipe_token);
	// 	pipe_token  = extract_token(&data->token);
	// 	command = get_copy_of_token(command, &pipe_token);
	// 	expand(command,data->env, &pipe_token);
	// 	redirections(&pipe_token);
	// 	redirect_input(&pipe_token);
	// 	join_nodes(&pipe_token);
	// 	tree[j] = get_copy_of_token_v3(tree[j], &pipe_token);
	// 	j++;
	// }
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
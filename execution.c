/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:49:01 by ibougajd          #+#    #+#             */
/*   Updated: 2024/09/23 13:27:35 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	normal_execution(t_data *data)
{
	char **command;

	command = NULL;
	command = get_copy_of_token(command, &(data->token));
	
	
	if(data->lexer.dollar)
		expand(command,data->env, data);
	if (data->lexer.redirect_output)
	{
		redirections(data);
	}
	if (data->lexer.redirect_input)
		redirect_input(data);
	
	command = get_copy_of_token_v3(command, &(data->token));
	if(!command)
		return;
	execute(command, data->env);
}
void	pipe_execution(int i, t_data *data)
{
	int		j;
	char	***tree;
	
	tree = NULL;
	j = 0;
	tree = malloc((i + 1) * sizeof(char **));
	while(j <= i)
	{
		tree[j] = get_copy_of_token_version_tow(tree[j],&data->token);
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
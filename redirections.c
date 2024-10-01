/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 04:21:31 by ibougajd          #+#    #+#             */
/*   Updated: 2024/10/01 04:21:33 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int  redirect_input(t_token **token, t_data *data)
{
	t_token *tmp = *token;
	int fd = 0;
	while(tmp)
	{
		if (tmp->type == HERDOK)
		{
			fd = heredoc(&tmp, data);
			tmp = tmp->next->next;
		}
		else if(tmp->type == INPUT_REDIRECTION)
		{
			fd = open(tmp->next->arg, O_RDONLY);
			tmp = tmp->next->next;
		}
		else if(tmp)
			tmp = tmp->next;

	}
	return fd;
}

int redirections(t_token **token)
{
	int i = 0;
	t_token *tmp = *token;
	int fd = 0;
	tmp = *token;
	i = 0;
	while(tmp)
	{
		if ((tmp->next) && (tmp->type == SINGLE_REDIRECTION || tmp->type == APPEND_REDIRECTION))
		{
			if (tmp->type == APPEND_REDIRECTION)
				fd  = open(tmp->next->arg, O_WRONLY | O_CREAT | O_APPEND, 0644);
			else
				fd  = open(tmp->next->arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		tmp = tmp->next;
	}
	// dup2(fd , STDOUT_FILENO);
	// close(fd);
	return(fd);
}

char *handle_redirections(char *command, t_data *data, char c)
{
	int i = 0;
	if(command[i] != c)
	{
		while(command[i] != c)
			i++;
		data->type = 0;
		command = add_command_to_node(command, i, data);
		return(command);
	}
	while(command[i] == c)
		i++;
	if(i == 1)
	{
		data->type = INPUT_REDIRECTION;
		if (c == '>')
			data->type = SINGLE_REDIRECTION;
		command = add_command_to_node(command, i, data);
	}
	else if(i == 2)
	{
		data->type = APPEND_REDIRECTION;
		if(c == '<')
			data->type = HERDOK;
		command = add_command_to_node(command, i, data);
	}
	else
	{
		data->syntax_error = 1;
		return (NULL);
	}
	return(command);
		
}
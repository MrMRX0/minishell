/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 14:48:47 by ibougajd          #+#    #+#             */
/*   Updated: 2024/10/02 02:14:39 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"




char *handle_quote(char *command , t_data *data, char c)
{
	int quote = 0;
	int i = 0;
	char s = '\'';
	if (c == '\'')
		s = '\"';
	if(command[0] == c)
	{
		quote = 1;
		i++;
	
		while(command[i])
		{
			if(command[i] != c)
				i++;
			
			if(command[i] == c)
			{
				quote++;
				i++;
			}
			if((quote % 2 == 0))
			{
				char letter = command[i];
				if(i == 2)
					return (command + 2);
				data->type = S_QUOTE;
				if (c == '\"')
					data->type = D_QUOTE;
				command = add_command_to_node(command, i, data);
				if(!command)
					return(NULL);
				t_token *tmp = data->token;
				while(tmp  && tmp->next)
					tmp = tmp->next;
				tmp->next_command = 0;
				if(letter != ' ' && letter != '\0' && letter != '>' && letter != '<' && letter != '|')
					tmp->next_command = 1; //set the flag to 1 to join the node later 
				return(command);
			}
		}
		data->syntax_error = 1;
		return(NULL);
	}
	else
	{
		while(command[i] != c)
			i++;
		data->type = 0;
		command = add_command_to_node(command, i , data);
		t_token *tmp = data->token;
		while(tmp  && tmp->next)
			tmp = tmp->next;
		tmp->next_command = 1; //set the flag to 1 to join the node later 
		return(command);
	}
		
	return(NULL);
}


//USER
//USER



void ft_syntax_error(t_data *data)
{
	write(2, "syntax Error\n", 14);
	data->exit_status = 2;
}
char *handle_pipe(char *command, t_data *data)
{
	int i = 0;
	int b = 0;
	
	while(command[i] != '|')
		i++;
	if(i)
	{
		data->type = 0;
		command = add_command_to_node(command, i, data);
		return(command);
	}
	i = 1;
	while(command[i] != '|' && command[i] != '\0')
	{
		if (command[i] == ' ')
			i++;
		else
		{
			b++;
			i++;
		}			// exit(0);
	}
	if(b == 0)
	{
		data->syntax_error = 1;
		return(NULL);
	}
	data->type = PIPE;
	command = add_command_to_node(command, 1, data);


	return(command);
}
int parser(t_data *data)
{
	t_token *tmp;

	tmp = data->token;
	if(!tmp)
		return(0);
	while(tmp)
	{
		if(tmp->type == SINGLE_REDIRECTION || tmp->type == APPEND_REDIRECTION || tmp->type == HERDOK || tmp->type == INPUT_REDIRECTION )
		{
			if (!tmp->next)
				return(ft_syntax_error(data), 1);
			if(tmp->next->type == SINGLE_REDIRECTION || tmp->next->type == APPEND_REDIRECTION)
				return(ft_syntax_error(data), 1);
			if(tmp->next->type == HERDOK || tmp->next->type == INPUT_REDIRECTION)
				return(ft_syntax_error(data), 1);
			if(tmp->next->type == PIPE)
				return(ft_syntax_error(data), 1);
		}
		tmp = tmp->next;
	}
	return(0);
}
int parsing(char *command, t_data *data)
{
	int i;
	
	i = 0;
	if(*command == '\n')
	{
		data->exit_status = 0;
		return(1);
	}
	data->syntax_error = 0;
	while(command[i] != '\0')
	{
		command = remove_white_spaces(command);
		if(!command)
			return(0);
		while(command[i] != '\"' && command[i] != ' '  && command[i] != '\0' && command[i] != '\'' && command[i] != '>' && command[i] != '|' && command[i] != '<')
			i++;
		if (command[i] == ' ' || command[i] == '\0')
		{
			data->type = 0;
			command = add_command_to_node(command, i,data);
		}
		else if (command[i] == '\"')
			command = handle_quote(command, data, '\"');
		else if (command[i] == '\'')
			command = handle_quote(command, data, '\'');
		else if (command[i] == '>')
			command = handle_redirections(command, data, '>');
		else if (command[i] == '|')
			command = handle_pipe(command, data);
		else if (command[i] == '<')
			command = handle_redirections(command, data, '<');
		if(data->syntax_error)
			return(ft_syntax_error(data), 1);
		if(!command)
			return(0);
		i = 0;
	}

	return(0);
}

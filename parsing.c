/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 14:48:47 by ibougajd          #+#    #+#             */
/*   Updated: 2024/09/26 16:02:15 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char *add_command_to_node(char *command, int i, t_data *data)
{
	int j;

	j = 0;
	ft_lst_add(&data->token);
	t_token *tmp = data->token;
	while(tmp->next)
		tmp = tmp->next;
	tmp->arg = malloc(i * sizeof(char));
	tmp->type = data->type;
	while(j < i)
	{
		tmp->arg[j] = command[j];
		j++;
	}
	tmp->arg[j] = '\0';
	// printf("%s\n", tmp->arg);
	if(!command[i])
		return(NULL);
	return(command + i);
}

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
		ft_syntax_error(data);
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
		ft_syntax_error(data);
		return (NULL);
	}
	return(command);
		
}
//USER
//USER
int str_cmp_n(char *str1, char *str2, int n)
{
	while((*str1 != '\0') && (*str1 == *str2))
	{
		n--;
		(str1)++;
		(str2)++;
	}
	if (n == 0 && *str1 == '\0')
		return 0;
	return 1;
}
char *handle_dollar_sign(char *str, t_data *data, int *b)
{
	int i = 0;
	int j = 0;
	char **splited_env;
	if(str_cmp_n("?", str, 1) == 0)
	{
		char *res = NULL;
		res = ft_itoa(data->status);
		return(*b += 1, res);
	}
	while(str[i])
	{
		if((str[i] != '$' && str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122) || (str[i] >= '0' && str[i] <= '9'))
			i++;
		else	
			break;
	}
	if(!i)
		return("$");
	while(data->env[j])
	{
		splited_env = ft_split(data->env[j], '=');
		if(str_cmp_n(splited_env[0], str, i) == 0)
		{
			return(*b += (i), splited_env[1]);
		}
		j++;
	}
	return(*b += i,NULL);
}
char **expand(char** argv, t_data *data, t_token **token)
{
	int i;
	int b;
	char *final_str = NULL;
	char *returned_str = NULL;
	char *str = NULL;
	char tmp[2];
	t_token *hold = *token;

	i = 0;
	b = 0;
	while(argv[i])
	{
		str = argv[i];
		b = 0;
		if(((strchr(str, '$')) && ((*token)->type == S_QUOTE || (*token)->type == HERDOK_INPUT))  || (strchr(str, '$') == 0))
		{
			i++;
			*token = (*token)->next;
		}
		else if ((strchr(str, '$')))
		{
			while(str[b])
			{
				//$USERasdf
				if(str[b] == '$')
				{
					b++;
					returned_str = handle_dollar_sign(str + b, data, &b);
					if(returned_str)
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
			argv[i] = final_str;
			(*token)->arg = final_str;
			final_str = NULL;
			returned_str = NULL;
			*token = (*token)->next;
			i++;	
		}	
	}
	*token = hold;
	return(argv);
}
void lexer(char *command, t_data *data)
{
	int i;
	
	i = 0;
	while(command[i])
	{
		data->lexer.dollar += (command[i] == '$');
		data->lexer.redirect_output += (command[i] == '>');
		data->lexer.redirect_input += (command[i] == '<');
		data->lexer.pipe += (command[i] == '|');
		data->lexer.single_quote += (command[i] == '\'');
		data->lexer.double_quote += (command[i] == '\"');
		i++;
	}
}
void ft_syntax_error(t_data *data)
{
	printf("syntax Error\n");
	data->syntax_error = 1;
	// exit(1);
}
char * handle_pipe(char *command, t_data *data)
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
		ft_syntax_error(data);
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
	while(tmp->next)
	{
		if(tmp->type == SINGLE_REDIRECTION || tmp->type == APPEND_REDIRECTION || tmp->type == HERDOK || tmp->type == INPUT_REDIRECTION )
		{
			if(tmp->next->type == SINGLE_REDIRECTION || tmp->next->type == APPEND_REDIRECTION)
				ft_syntax_error(data);
			else if(tmp->next->type == HERDOK || tmp->next->type == INPUT_REDIRECTION)
				ft_syntax_error(data);
			else if(tmp->next->type == PIPE)
				ft_syntax_error(data);
			if(data->syntax_error)
				return(1);
			
		}
		tmp = tmp->next;
	}
	return(0);
}
int parsing(char *command, t_data *data)
{
	int i;
	
	i = 0;
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
			return(1);
		if(!command)
			return(0);
		i = 0;
	}
	return(0);
}

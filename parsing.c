/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 14:48:47 by ibougajd          #+#    #+#             */
/*   Updated: 2024/09/01 17:10:10 by ibougajd         ###   ########.fr       */
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
	}
	while(command[i])
	{
		if(command[i] != c)
			i++;
		if(command[i] == c)
		{
			quote++;
			i++;
		}
		if((quote % 2 == 0) && (command[i] == ' '  || command[i] == '\0' || command[i] == s || command[i] == c || command[i] == '>'))
		{
			if(i == 2)
				return (command + 2);
			if(command[i] == s || command[i] == c)
			{
				t_token *tmp = data->token;
				while(tmp  && tmp->next)
					tmp = tmp->next;
				tmp->next_command = 1; //set the flag to 1 to join the token later 
			}
            data->type = S_QUOTE;
            if (c == '\"')
                data->type = D_QUOTE;
			command = add_command_to_node(command, i, data);
			if(!command)
				return(NULL);
			return(command);
		}
	}
	return(ft_exit(data), NULL);
}

char *handle_redirections(char *command, t_data *data)
{
	int i = 0;
    while(command[i] != '>')
        i++;
    if(i)
       command = add_command_to_node(command, i, data);
    // printf("comand after cut it==%s\n",command);
    i = 0;
    if(command[i + 2] == '>')
        ft_exit(data);
	else if(command[i + 1] != '>')
	{
		data->type = SINGLE_REDIRECTION;
		command = add_command_to_node(command, i + 1, data);
	}
	else if(command[i + 1] == '>')
	{
		data->type = APPEND_REDIRECTION;
		command = add_command_to_node(command, i + 2, data);
	}
    return(command);
		
}

char *handle_dollar_sign(char *str, char **env, int *b)
{
	int i = 0;
	int j = 0;
	char **splited_env;
	// printf("<<str>>%s\n",str);
	while(str[i])
	{
		if((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122) || (str[i] >= '0' && str[i] <= '9'))
			i++;
		else	
			break;
	}
	if(!i)
		return("$");
	// printf("%d\n",i);
	while(env[j])
	{
		splited_env = ft_split(env[j], '=');
		if(strncmp(str, splited_env[0], i) == 0)
		{
			
			// printf("splited_env>>%s\n",splited_env[0]);
			// printf("str>>%s\n",str);
			return(*b += (i), splited_env[1]);
		}
		j++;
	}
	return(*b += i,NULL);
}
char **expand(char** argv, char**env, t_data *data)
{
	int i;
	int b;
	int start;
	int end;

	i = 0;
	b = 0;
	start = 0;
	end = 0;
	char *final_str = NULL;
	char *returned_str = NULL;
	char *str = NULL;
	char tmp[2];
	while(argv[i])
	{
		str = argv[i];
		b = 0;
		if(!(strchr(str, '$')))
		{
			i++;
			data->token = data->token->next;
			continue;
		}
		if((strchr(str, '$')) && data->token->type == S_QUOTE)
		{
			i++;
			data->token = data->token->next;
			continue;
		}
		// printf("argv[%d]=%s\n", i, argv[i]);
		while(str[b])
		{
			if(str[b] == '$')
			{
				// exit(0);
				b++;
				returned_str = handle_dollar_sign(str + b, env, &b);
				// printf("str>after>%s\n",str);
				// printf("returned_str>>%s\n",returned_str);
				if(returned_str)
					final_str = ft_strjoin(final_str, returned_str);
				// printf("final str>%s\n",final_str);
			}
			else
			{
				// printf("final str>>%s\n", final_str);
				// printf("str[b]>>%c\n", str[b]);
				tmp[0] = str[b];
				tmp[1] = '\0';
				final_str = ft_strjoin(final_str, tmp);
				b++;
			}	
		}
		argv[i] = final_str;
		final_str = NULL;
		i++;
	}
	return(argv);
}

int comands_formater(char *command, char**args, t_data *data)
{
	int i;
	
	i = 0;
	(void)args;
	if(command[i] == '\0')
		return(1);
	while(command[i])
	{
		data->lexer.dollar += (command[i] == '$');
		data->lexer.redirect_input += (command[i] == '>');
		data->lexer.redirect_output += (command[i] == '<');
		data->lexer.pipe += (command[i] == '|');
		data->lexer.single_quote += (command[i] == '\'');
		data->lexer.double_quote += (command[i] == '\"');
		i++;
	}
	i = 0;
	while(command[i] != '\0')
	{
		command = remove_white_spaces(command);
		while(command[i] != '\"' && command[i] != ' '  && command[i] != '\0' && command[i] != '\'' && command[i] != '>')
			i++;
		if (command[i] == ' ' || command[i] == '\0')
		{
			
			command = add_command_to_node(command, i,data);
			if(!command)
				return(0);
			i = 0;
		}
		else if (command[i] == '\"')
		{
			command = handle_quote(command, data, '\"');
			if(!command)
				return(0);
			i = 0;
		}
		else if (command[i] == '\'')
		{
			command = handle_quote(command, data, '\'');
			if(!command)
				return(0);
			i = 0;
		}
		else if (command[i] == '>')
		{
			command = handle_redirections(command, data);
			if(!command)
				return(0);
			i = 0;
		}
	}
	return(0);
}
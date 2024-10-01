/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 04:21:01 by ibougajd          #+#    #+#             */
/*   Updated: 2024/10/01 04:21:03 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *extraxt_arg(char *arg)
{
	int i = 0;
	int b = 0;
	while(arg[i])
	{
		if (arg[i] == '\'')
			i++;
		else if (arg[i] == '\"')
			i++;
		else
		{
			i++;
			b++;
		}
	}
	i = 0;
	b = 0;
	char *new_arg = malloc((b + 1) * sizeof(char));
	while(arg[i])
	{
		if (arg[i] == '\'')
			i++;
		else if (arg[i] == '\"')
			i++;
		else
		{
			new_arg[b] = arg[i];
			i++;
			b++;
		}
		new_arg[b] = '\0';
	}
	return(new_arg);
}

int get_size_of_tree(t_token **token)
{
	int ret = 0;
	t_token *tmp = *token;
	if(!tmp)
		return 0;
	while(tmp->next)
	{
		if(tmp->type == PIPE)
			ret++;
		tmp = tmp->next;
	}
	return(ret);
}
void ft_error(char **cmd, t_data *data)
{
	write(2, cmd[0], ft_strlen(cmd[0]));
	write(2, ": command not found\n", 21);
	data->exit_status = 127;
	exit(data->exit_status);
}
int get_len(t_token *lst)
{
	int i;
	int b;
	
	i = 0;
	b = 0;
	while(lst->arg[i])
	{
		if(lst->arg[i] == '\"' && lst->type == D_QUOTE)
			i++;
		else if(lst->arg[i] == '\'' &&  lst->type == S_QUOTE)
			i++;
		else
		{
			b++;
			i++;
		}
	}
	return(b);
}

void get_copy(char *s1, t_token *lst)
{
	int i;
	int b;

	i = 0;
	b = 0;
	// printf("..%d %s\n", lst->type, lst->arg);
	while(lst->arg[i])
	{
		if(lst->arg[i] == '\"' && lst->type == D_QUOTE)
			i++;
		else if(lst->arg[i] == '\'' && lst->type == S_QUOTE)
			i++;
		else
		{
			s1[b] = lst->arg[i];
			b++;
			i++;
		}
	}
	s1[b] = '\0';
	//free lst after
	lst->arg = s1;
}
void get_copy_v3(char *s1, t_token *lst)
{
	int i;

	i = 0;
	// printf("..%d %s\n", lst->type, lst->arg);
	while(lst->arg[i])
	{
			s1[i] = lst->arg[i];
			i++;
	}
	s1[i] = '\0';
	//free lst after
	lst->arg = s1;
}
char *remove_white_spaces(char *str)
{
	int i = 0;
	while(str[i] == ' ' || str[i] == '	')
			i++;
	if(!str[i])
		return(NULL);
	return(str + i);
}

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
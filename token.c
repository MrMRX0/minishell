/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 04:21:10 by ibougajd          #+#    #+#             */
/*   Updated: 2024/10/01 06:39:47 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **get_copy_of_token_version_tow(char **argv, t_token **lst)
{
	int len = 0;
	t_token *tmp = *lst;
	while(tmp && tmp->type != PIPE)
	{
		tmp = tmp->next;
		len++;
	}
	tmp= *lst;
	argv = malloc(len * sizeof(char *) + 1);
	int i = 0;
	while(i < len)
	{
		// printf("len of arg[%d] is %d\n",i,get_len(tmp->arg));
		argv[i] = malloc(get_len(tmp) + 1);
		get_copy(argv[i], tmp);
		// printf("%s\n",argv[i]);
		tmp = tmp->next;
		i++;
		
	}
	argv[i] = NULL;
	free_n_lst(lst, len);
	return(argv);
}

char **get_copy_of_token_v3(char **argv, t_token **lst)
{
	int len = 0;
	if (!*lst)
		return(NULL);
	t_token *tmp = *lst;
	while(tmp)
	{
		if(tmp->type == HERDOK || tmp->type == SINGLE_REDIRECTION || tmp->type == APPEND_REDIRECTION || tmp->type == INPUT_REDIRECTION)
			tmp = tmp->next->next;
		else
		{
			tmp = tmp->next;
			len++;
		}
	}
	if(!len)
		return NULL;
	tmp= *lst;
	argv = malloc((len + 1) * sizeof(char *));
	int i = 0;
	while(tmp)
	{
		if(tmp->type == HERDOK || tmp->type == SINGLE_REDIRECTION || tmp->type == APPEND_REDIRECTION || tmp->type == INPUT_REDIRECTION)
			tmp = tmp->next->next;
		else
		{
			if(!tmp->arg)
			{
				argv[i] = NULL;
				tmp = tmp->next;
				i++;
			}
			else
			{
				argv[i] = malloc(ft_strlen(tmp->arg) + 1);
				get_copy_v3(argv[i], tmp);
				tmp = tmp->next;
				i++;
			}
		}
		
	}
	argv[i] = NULL;
	return(argv);

}

char **get_copy_of_token(char **argv, t_token **lst)
{
	(void)argv;
	int len = 0;
	if (!*lst)
		return(NULL);
	t_token *tmp = *lst;
	while(tmp)
	{
		tmp = tmp->next;
		len++;
	}
	tmp= *lst;
	argv = malloc((len + 1) * sizeof(char *));
	int i = 0;
	while(i < len)
	{
		// printf("len of arg[%d] is %d\n",i,get_len(tmp->arg));
		argv[i] = malloc(get_len(tmp) + 1);
		get_copy(argv[i], tmp);
		// printf("%s\n",argv[i]);
		tmp = tmp->next;
		i++;
		
	}
	argv[i] = NULL;
	return(argv);

}

void ft_lst_add(t_token **lst) 
{
	if (!*lst) {
		*lst = malloc(sizeof(t_token));
		if (!*lst) {
			perror("malloc failed");
			exit(EXIT_FAILURE);
		}
		(*lst)->arg = NULL;
		(*lst)->next = NULL;
		(*lst)->previous = NULL;
		(*lst)->next_command = 0;
		return;
	}
	t_token *current = *lst;
	while (current->next)
		current = current->next;
	t_token *new_node = malloc(sizeof(t_token));
	if (!new_node)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	new_node->arg = NULL;
	new_node->next = NULL;
	new_node->next_command = 0;
	current->next = new_node;
	new_node->previous = current;
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

void join_nodes(t_token **token)
{
	t_token *tmp = *token;
	t_token *to_free;
	char *to_free_2 = NULL;
	while(tmp)
	{
		if (tmp->next_command == 1 && !tmp->next)
			return;
		if(tmp->next_command == 1 && tmp->next)
		{
			to_free_2 = tmp->arg;
			tmp->arg = ft_strjoin(tmp->arg, tmp->next->arg);
			free(to_free_2);
			to_free = tmp->next;
			if(to_free->next)
				tmp->next = to_free->next;
			else
				tmp->next = NULL;
			tmp->type = 0;
			if(to_free->next_command == 0)
				tmp->next_command = 0;
			free(to_free->arg);
			free(to_free);
		}
		if (tmp->next_command == 0)
			tmp = tmp->next;
	}
}
char *add_command_to_node(char *command, int i, t_data *data)
{
	int j;

	j = 0;
	ft_lst_add(&data->token);
	t_token *tmp = data->token;
	while(tmp->next)
		tmp = tmp->next;
	tmp->arg = malloc(i * sizeof(char) + 1);
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

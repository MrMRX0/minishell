/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 04:21:01 by ibougajd          #+#    #+#             */
/*   Updated: 2024/10/03 10:48:24 by ibougajd         ###   ########.fr       */
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
void ft_error(t_data *data, char *arg, char *error ,int exit_status)
{
	write(2, "minishell: ", 12);
	if(arg)
		write(2, arg, ft_strlen(arg));
	if(error)
		write(2, error, ft_strlen(error));
	data->exit_status = exit_status;
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

char *get_copy(t_token *lst)
{
	int i;
	int b;
	char *copy;

	i = 0;
	b = 0;
	copy = malloc((get_len(lst) + 1) * sizeof(char));
	while(lst->arg[i])
	{
		if(lst->arg[i] == '\"' && lst->type == D_QUOTE)
			i++;
		else if(lst->arg[i] == '\'' && lst->type == S_QUOTE)
			i++;
		else
		{
			copy[b] = lst->arg[i];
			b++;
			i++;
		}
	}
	copy[b] = '\0';
	free(lst->arg);
	lst->arg = ft_strdup(copy);
	return(copy);
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

// #define BUFFER_SIZE 1024

// Function to read a line of input from stdin
// char *readline_dyali() {
//     char *buffer = NULL;
//     int position = 0;
//     int buffer_size = BUFFER_SIZE;
//     char ch;

//     // Allocate the initial memory for the buffer
//     buffer = malloc(sizeof(char) * buffer_size);
//     if (!buffer) {
//         fprintf(stderr, "Allocation error\n");
//         return NULL;
//     }

//     // Read characters one by one
// 	printf(COLOR_BOLD_RED "➜  minishell " COLOR_RESET);
//     while (1) {
//         ch = getchar();  // Get the next character from stdin

//         // Check for end of input or new line
//         if (ch == EOF || ch == '\n') {
//             buffer[position] = '\0';  // Null-terminate the string
//             return buffer;
//         } else {
//             buffer[position] = ch;
//         }
//         position++;

//         // If the buffer is exceeded, reallocate memory
//         if (position >= buffer_size) {
//             buffer_size += BUFFER_SIZE;
//             buffer = realloc(buffer, buffer_size);
//             if (!buffer) {
//                 fprintf(stderr, "Reallocation error\n");
//                 return NULL;
//             }
//         }
//     }
// }
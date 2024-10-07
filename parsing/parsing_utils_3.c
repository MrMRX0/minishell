/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 04:21:01 by ibougajd          #+#    #+#             */
/*   Updated: 2024/10/07 09:07:37 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incld/minishell.h"

int	get_size_of_tree(t_token **token)
{
	int		ret;
	t_token	*tmp;

	ret = 0;
	tmp = *token;
	if (!tmp)
		return (0);
	while (tmp->next)
	{
		if (tmp->type == PIPE)
			ret++;
		tmp = tmp->next;
	}
	return (ret);
}

void	ft_error(t_data *data, char *arg, char *error, int exit_status)
{
	write(2, "minishell: ", 12);
	if (arg)
		write(2, arg, ft_strlen(arg));
	if (error)
		write(2, error, ft_strlen(error));
	data->exit_status = exit_status;
}

int	get_len(t_token *lst)
{
	int	i;
	int	b;

	i = 0;
	b = 0;
	while (lst->arg[i])
	{
		if (lst->arg[i] == '\"' && lst->type == D_QUOTE)
			i++;
		else if (lst->arg[i] == '\'' && lst->type == S_QUOTE)
			i++;
		else
		{
			b++;
			i++;
		}
	}
	return (b);
}

char	*get_copy(t_token *lst)
{
	int		i;
	int		b;
	char	*copy;

	i = 0;
	b = 0;
	copy = ft_malloc((get_len(lst) + 1) * sizeof(char));
	while (lst->arg[i])
	{
		if (lst->arg[i] == '\"' && lst->type == D_QUOTE)
			i++;
		else if (lst->arg[i] == '\'' && lst->type == S_QUOTE)
			i++;
		else
		{
			copy[b] = lst->arg[i];
			b++;
			i++;
		}
	}
	copy[b] = '\0';
	lst->arg = ft_strdup(copy);
	return (copy);
}

char	*remove_white_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '	')
		i++;
	if (!str[i])
		return (NULL);
	return (str + i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 01:49:45 by ibougajd          #+#    #+#             */
/*   Updated: 2024/10/14 01:57:16 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incld/minishell.h"

void	get_the_size_of_splited_arr(t_token *tmp, char *final_str)
{
	char	**splited_arr;

	splited_arr = ft_split_with_tabs(final_str, ' ');
	if (splited_arr)
		tmp->is_splited = get_size_of_double_array(splited_arr);
}

int	count_dollars(char **argv, t_token *token)
{
	int	i;
	int	d;

	i = 0;
	d = 0;
	while (argv[i] && token)
	{
		if (find_dollar_sign(argv[i], token))
			d++;
		i++;
		token = token->next;
	}
	return (d);
}

int	get_total_len(t_token *token)
{
	int	len;

	len = 0;
	while (token)
	{
		len += token->is_splited;
		token = token->next;
	}
	return (len);
}

void	not_z(t_token *tmp, t_token **new, char *str)
{
	t_token	*tmp2;

	ft_lst_add(new);
	tmp2 = *new;
	while (tmp2->next)
		tmp2 = tmp2->next;
	tmp2->arg = ft_strdup(str);
	tmp2->next_command = tmp->next_command;
	tmp2->num = tmp->num;
	tmp2->type = tmp->type;
}

void	avec_z(t_token **new, char *str)
{
	t_token	*tmp2;

	ft_lst_add(new);
	tmp2 = *new;
	while (tmp2->next)
		tmp2 = tmp2->next;
	tmp2->arg = ft_strdup(str);
	tmp2->next_command = 0;
	tmp2->num = 0;
	tmp2->type = 0;
}

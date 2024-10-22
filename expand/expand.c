/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-bou <nait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:03:33 by ibougajd          #+#    #+#             */
/*   Updated: 2024/10/22 12:41:23 by nait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incld/minishell.h"

void	fill_sub_array(t_token *tmp, char **new_arr, t_token **new, int *j)
{
	int		z;
	char	**splited_arr;

	z = 0;
	splited_arr = ft_split_with_tabs(tmp->arg, ' ');
	if (splited_arr)
	{
		while (splited_arr[z])
		{
			if (!z)
			{
				new_arr[*j] = ft_strdup(splited_arr[z]);
				not_z(tmp, new, splited_arr[z]);
			}
			else
			{
				new_arr[*j] = ft_strdup(splited_arr[z]);
				avec_z(new, splited_arr[z]);
			}
			z++;
			(*j)++;
		}
		free_double_char(splited_arr);
	}
}

void	add_to_node(t_token **new, t_token *tmp)
{
	t_token	*tmp2;

	ft_lst_add(new);
	tmp2 = *new;
	while (tmp2->next)
		tmp2 = tmp2->next;
	tmp2->arg = ft_strdup(tmp->arg);
}

char	**fill_new_array(t_token **token)
{
	int		len ;
	t_token	*tmp;
	t_token	*new;
	char	**new_arr;
	int		j;

	tmp = *token;
	len = get_total_len(tmp);
	new_arr = ft_malloc((len + 1) * sizeof(char *));
	tmp = *token;
	new = NULL;
	j = 0;
	while (tmp)
	{
		if (tmp->type != D_QUOTE)
			fill_sub_array(tmp, new_arr, &new, &j);
		else
			add_to_node(&new, tmp);
		tmp = tmp->next;
	}
	new_arr[j] = NULL;
	*token = new;
	return (new_arr);
}

char	**expand(char **argv, t_data *data, t_token **token)
{
	t_token			*tmp;
	char			*final_str;
	static int		i;

	tmp = *token;
	if (!count_dollars(argv, tmp))
		return (argv);
	while (argv[i] && tmp)
	{
		if (find_dollar_sign(argv[i], tmp))
		{
			final_str = expander(argv[i], data);
			argv[i] = final_str;
			if (tmp->type != D_QUOTE)
				get_the_size_of_splited_arr(tmp, final_str);
			else
				tmp->is_splited = 1;
			(tmp)->arg = ft_strdup(final_str);
		}
		else
			tmp->is_splited = 1;
		tmp = (tmp)->next;
		i++;
	}
	return (i = 0, fill_new_array(token));
}

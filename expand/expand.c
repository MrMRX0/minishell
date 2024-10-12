/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:03:33 by ibougajd          #+#    #+#             */
/*   Updated: 2024/10/12 05:25:10 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incld/minishell.h"
int	count_words(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s == c || *s == '\t')
			in_word = 0;
		else if (in_word == 0)
		{
			in_word = 1;
			count++;
		}
		s++;
	}
	return (count);
}

char	*get_next_word(const char **s, char c)
{
	const char	*start;
	const char	*end;
	char		*word;

	while (**s == c || **s == '\t')
		(*s)++;
	start = *s;
	while (**s && **s != c && **s != '\t')
		(*s)++;
	end = *s;
	word = ft_substr(start, 0, end - start);
	return (word);
}

char	**ft_split_with_tabs(char const *s, char c)
{
	char	**res;
	int		word_count;
	int		i;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	res = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		res[i] = get_next_word(&s, c);
		if (!res[i])
		{
			while (i > 0)
				free(res[--i]);
			free(res);
			return (NULL);
		}
		i++;
	}
	return (res[i] = NULL, res);
}

char	*expander(char *str, t_data *data)
{
	int		b;
	char	*final_str;
	char	c[2];

	final_str = NULL;
	b = 0;
	while (str[b])
	{
		if (str[b] == '$' && ++b)
			final_str = get_last_res(str, data, &b, final_str);
		else
		{
			c[0] = str[b];
			c[1] = '\0';
			final_str = ft_strjoin(final_str, c);
			b++;
		}
	}
	return (final_str);
}

int	get_size_of_double_array(char **arr)
{
	int i;

	i = 0;
	if(!arr)
		return(0);
	while(arr[i])
		i++;
	return(i);
}

char	**expand(char **argv, t_data *data, t_token **token)
{
	t_token	*tmp;
	char	*final_str;
	int		i;
	char	**splited_arr;

	tmp = *token;
	final_str = NULL;
	splited_arr = NULL;
	i = 0;
	int d = 0;
	while (argv[i] && tmp)
	{
		if (find_dollar_sign(argv[i], tmp))
		{
			d++;
		}
		i++;
		tmp = (tmp)->next;
	}
	if(!d)
		return(argv);
	i = 0;
	tmp = *token;
	while (argv[i] && tmp)
	{
		if (find_dollar_sign(argv[i], tmp))
		{
			final_str = expander(argv[i], data);
			argv[i] = final_str;
			if(tmp->type != D_QUOTE)
			{
				splited_arr = ft_split_with_tabs(final_str, ' ');
				if(splited_arr)
					tmp->is_splited = get_size_of_double_array(splited_arr);
			}
			else
				tmp->is_splited = 1;
			(tmp)->arg = ft_strdup(final_str);
		}
		tmp = (tmp)->next;
		i++;
	}
	int len = 0;
	tmp = *token;
	while(tmp)
	{
		len+= tmp->is_splited;	
		tmp = tmp->next;
	}
	char **new_arr = ft_malloc((len + 1) * sizeof(char *));
	tmp = *token;
	int z = 0;
	int j = 0;
	t_token *new;
	t_token *tmp2;
	new = NULL;
	while(tmp)
	{
		if(tmp->type != D_QUOTE)
		{
			splited_arr = ft_split_with_tabs(tmp->arg, ' ');
			if(splited_arr)
			{
				while(splited_arr[z])
				{
					if(!z)
					{
						new_arr[j] = ft_strdup(splited_arr[z]);
						ft_lst_add(&new);
						tmp2 = new;
						while(tmp2->next)
							tmp2 = tmp2->next;
						tmp2->arg = ft_strdup(splited_arr[z]);
						tmp2->next_command = tmp->next_command;
						tmp2->num = tmp->num;
						tmp2->type = tmp->type;
						
					}
					else
					{
						new_arr[j] = ft_strdup(splited_arr[z]);
						ft_lst_add(&new);
						tmp2 = new;
						while(tmp2->next)
							tmp2 = tmp2->next;
						tmp2->arg = ft_strdup(splited_arr[z]);
						tmp2->next_command = 0;
						tmp2->num = 0;
						tmp2->type = 0;
					}
					z++;
					j++;	
				}
				
			}
		}
		else
		{
			ft_lst_add(&new);
			tmp2 = new;
			while(tmp2->next)
				tmp2 = tmp2->next;
			tmp2->arg = ft_strdup(tmp->arg);
		}
		tmp = tmp->next;
		z = 0;
	}
	new_arr[j] = NULL;
	*token = new;
	return (new_arr);
}

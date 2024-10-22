/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-bou <nait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 01:49:10 by ibougajd          #+#    #+#             */
/*   Updated: 2024/10/22 12:31:56 by nait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incld/minishell.h"

int	ccount_words(const char *s, char c)
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

char	*gget_next_word(const char **s, char c)
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
	word_count = ccount_words(s, c);
	res = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		res[i] = gget_next_word(&s, c);
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
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

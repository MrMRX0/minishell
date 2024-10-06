/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:03:33 by ibougajd          #+#    #+#             */
/*   Updated: 2024/10/04 20:56:21 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incld/minishell.h"

char	*expander(char *str, t_data *data)
{
	int		b;
	char	*tmp_free;
	char	*final_str;
	char	c[2];

	final_str = NULL;
	tmp_free = NULL;
	b = 0;
	while (str[b])
	{
		if (str[b] == '$' && ++b)
			final_str = get_last_res(str, data, &b, final_str);
		else
		{
			c[0] = str[b];
			c[1] = '\0';
			tmp_free = final_str;
			final_str = ft_strjoin(final_str, c);
			free(tmp_free);
			b++;
		}
	}
	return (final_str);
}

char	**expand(char **argv, t_data *data, t_token **token)
{
	t_token	*tmp;
	char	*final_str;
	int		i;

	tmp = *token;
	final_str = NULL;
	i = 0;
	while (argv[i] && tmp)
	{
		if (find_dollar_sign(argv[i], tmp))
		{
			final_str = expander(argv[i], data);
			free(argv[i]);
			argv[i] = final_str;
			free((tmp)->arg);
			(tmp)->arg = ft_strdup(final_str);
		}
		tmp = (tmp)->next;
		i++;
	}
	return (argv);
}

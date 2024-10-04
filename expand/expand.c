/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 04:22:21 by ibougajd          #+#    #+#             */
/*   Updated: 2024/10/03 18:35:02 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expander(char *str, t_data *data)
{
	int		b;
	char	*returned_str = NULL;
	char	*tmp_free = NULL;
	char	*final_str = NULL;
	char	c[2];

	b = 0;
	while (str[b])
	{
		if (str[b] == '$')
		{
			b++;
			returned_str = handle_dollar_sign(str + b, data, &b);
			if (returned_str)
			{
				tmp_free = final_str;
				final_str = ft_strjoin(final_str, returned_str);
				if (tmp_free)
					free(tmp_free);
				free(returned_str);
			}
		}
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

int	find_dollar_sign(char *str, t_token *tmp)
{
	if (((strchr(str, '$')) && ((tmp)->type == S_QUOTE
				|| (tmp)->type == HERDOK_INPUT)) || (strchr(str, '$') == 0))
		return (0);
	else if ((strchr(str, '$')))
		return (1);
	return (0);
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

char	*get_value(char **env, char *str, int i)
{
	char	**splited_env;
	char	*value;
	int		j;

	value = NULL;
	j = 0;
	while (env[j])
	{
		splited_env = NULL;
		splited_env = ft_split(env[j], '=');
		if (str_cmp_n(splited_env[0], str, i) == 0)
		{
			free(splited_env[0]);
			value = ft_strdup(splited_env[1]);
			free(splited_env[1]);
			free(splited_env);
			return (value);
		}
		free_double_char(splited_env);
		j++;
	}
	return (NULL);
}

char	*handle_dollar_sign(char *str, t_data *data, int *b)
{
	int		i;
	char	*value;
	char	*res;

	i = 0;
	value = NULL;
	if (str_cmp_n("?", str, 1) == 0)
	{
		res = ft_itoa(data->exit_status);
		return (*b += 1, res);
	}
	while (str[i])
	{
		if ((str[i] != '$' && str[i] >= 65 && str[i] <= 90) || (str[i] >= 97
				&& str[i] <= 122) || (str[i] >= '0' && str[i] <= '9'))
			i++;
		else
			break ;
	}
	if (!i)
		return (ft_strdup("$"));
	value = get_value(data->env, str, i);
	if (value)
		return (*b += i, value);
	return (*b += i, NULL);
}

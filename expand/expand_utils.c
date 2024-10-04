/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:04:57 by ibougajd          #+#    #+#             */
/*   Updated: 2024/10/04 20:56:21 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incld/minishell.h"

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

int	find_dollar_sign(char *str, t_token *tmp)
{
	if (((strchr(str, '$')) && ((tmp)->type == S_QUOTE
				|| (tmp)->type == HERDOK_INPUT)) || (strchr(str, '$') == 0))
		return (0);
	else if ((strchr(str, '$')))
		return (1);
	return (0);
}

char	*get_last_res(char *str, t_data *data, int *b, char *final_str)
{
	char	*returned_str;
	char	*tmp_free;

	returned_str = NULL;
	tmp_free = NULL;
	returned_str = handle_dollar_sign(str + *b, data, b);
	if (returned_str)
	{
		tmp_free = final_str;
		final_str = ft_strjoin(final_str, returned_str);
		if (tmp_free)
			free(tmp_free);
		free(returned_str);
	}
	return (final_str);
}

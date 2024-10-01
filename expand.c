/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 04:22:21 by ibougajd          #+#    #+#             */
/*   Updated: 2024/10/01 04:46:19 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **expand(char** argv, t_data *data, t_token **token)
{
	int i;
	int b;
	char *final_str = NULL;
	char *returned_str = NULL;
	char *str = NULL;
	char *tmp_free = NULL;
	char tmp[2];
	t_token *hold = *token;

	i = 0;
	b = 0;
	while(argv[i] && *token)
	{
		str = argv[i];
		b = 0;
		if(((strchr(str, '$')) && ((*token)->type == S_QUOTE || (*token)->type == HERDOK_INPUT))  || (strchr(str, '$') == 0))
		{
			i++;
			*token = (*token)->next;
		}
		else if ((strchr(str, '$')))
		{
			while(str[b])
			{
				if(str[b] == '$')
				{
					b++;
					returned_str = handle_dollar_sign(str + b, data, &b);
					if(returned_str)
					{
						// tmp_free = final_str;
						final_str = ft_strjoin(final_str, returned_str);
						// if(tmp_free)
						// 	free(tmp_free);
						// free(returned_str);
					}
				}
				else
				{
					tmp[0] = str[b];
					tmp[1] = '\0';
					// tmp_free = final_str;
					final_str = ft_strjoin(final_str, tmp);
					// free(tmp_free);
					b++;
				}	
			}
			// free(argv[i]);
			argv[i] = final_str;
			// free((*token)->arg);
			(*token)->arg = final_str;
			final_str = NULL;
			returned_str = NULL;
			*token = (*token)->next;
			i++;	
		}	
	}
	*token = hold;
	return(argv);
}

char *handle_dollar_sign(char *str, t_data *data, int *b)
{
	int i = 0;
	int j = 0;
    int e = 0;
	char **splited_env;
	if(str_cmp_n("?", str, 1) == 0)
	{
		char *res = NULL;
		res = ft_itoa(data->exit_status);
		return(*b += 1, res);
	}
	while(str[i])
	{
		if((str[i] != '$' && str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122) || (str[i] >= '0' && str[i] <= '9'))
			i++;
		else	
			break;
	}
	if(!i)
		return("$");
	while(data->env[j])
	{
		splited_env = ft_split(data->env[j], '=');
		if(str_cmp_n(splited_env[0], str, i) == 0)
		{
			free(splited_env[0]);
			return(*b += (i), splited_env[1]);
		}
		while(splited_env[e])
		{
			free(splited_env[e]);
			e++;
		}
        e = 0;
		j++;
	}
	return(*b += i,NULL);
}

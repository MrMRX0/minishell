/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 04:21:10 by ibougajd          #+#    #+#             */
/*   Updated: 2024/10/04 20:59:10 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incld/minishell.h"

int	get_len_v2(t_token **token)
{
	t_token	*tmp;
	int		i;

	tmp = *token;
	i = 0;
	while (tmp)
	{
		if (tmp->type == HERDOK || tmp->type == S_R || tmp->type == A_R
			|| tmp->type == I_R)
			tmp = tmp->next->next;
		else
		{
			tmp = tmp->next;
			i++;
		}
	}
	return (i);
}

char	**get_copy_of_token_v2_handler(t_token **tmp, char **argv, int len)
{
	int	i;

	i = 0;
	argv = malloc((len + 1) * sizeof(char *));
	while ((*tmp))
	{
		if ((*tmp)->type == HERDOK || (*tmp)->type == S_R || (*tmp)->type == A_R
			|| (*tmp)->type == I_R)
			(*tmp) = (*tmp)->next->next;
		else
		{
			if (!(*tmp)->arg)
				argv[i] = NULL;
			else
				argv[i] = ft_strdup((*tmp)->arg);
			(*tmp) = (*tmp)->next;
			i++;
		}
	}
	return (argv[i] = NULL, argv);
}

char	**get_copy_of_token_v2(char **argv, t_token **lst)
{
	int		len;
	t_token	*tmp;

	if (!*lst)
		return (NULL);
	tmp = *lst;
	len = get_len_v2(lst);
	if (!len)
		return (NULL);
	argv = get_copy_of_token_v2_handler(&tmp, argv, len);
	return (argv);
}

char	**get_copy_of_token_v1(char **argv, t_token **lst)
{
	int		len;
	t_token	*tmp;
	int		i;

	len = 0;
	if (!*lst)
		return (NULL);
	tmp = *lst;
	while (tmp)
	{
		tmp = tmp->next;
		len++;
	}
	tmp = *lst;
	argv = malloc((len + 1) * sizeof(char *));
	i = 0;
	while (i < len)
	{
		argv[i] = get_copy(tmp);
		tmp = tmp->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

int	str_cmp_n(char *str1, char *str2, int n)
{
	while ((*str1 != '\0') && (*str1 == *str2))
	{
		n--;
		(str1)++;
		(str2)++;
	}
	if (n == 0 && *str1 == '\0')
		return (0);
	return (1);
}

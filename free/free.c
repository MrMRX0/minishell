/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:43:47 by nait-bou          #+#    #+#             */
/*   Updated: 2024/10/04 21:46:42 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incld/minishell.h"

void   free_av(char **av)
{
    int i;

    i = 0;
    if(!av)
        return ;
    while (av[i])
    {
        free(av[i]);
        i++;
    }
    free(av);
}

void free_env(t_env **env)
{
    t_env *tmp;
    t_env *tmp2;

    tmp = *env;
    while (tmp)
    {
        tmp2 = tmp->next;
        free(tmp->key);
        free(tmp->value);
        tmp = tmp2;
    }
    *env = NULL;
}

void    free_close_all(t_data *data, char **av)
{
    free_av(av);
    free_av(data->env);
    free_env(&(data)->env_list);
}
void	ft_free(t_data *data)
{
	free_linked_list(&data->token);
	return ;
}
void free_n_lst(t_token **lst, int len)
{
	int i = 0;
	t_token *tmp = NULL;
	while(*lst && i <= len)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp);
		i++;
	}
}
void free_linked_list(t_token **lst)
{
	if(!*lst)
		return ;
	t_token *tmp = NULL;
	while(*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
        free(tmp->arg);
		free(tmp);
	}
}

void free_double_char(char **str)
{
    int i;

    i = 0;
    if(!str)
        return;
    while(str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-bou <nait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:43:47 by nait-bou          #+#    #+#             */
/*   Updated: 2024/09/26 12:25:56 by nait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void   free_av(char **av)
{
    int i;

    i = 0;
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
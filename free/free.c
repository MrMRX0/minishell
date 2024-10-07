/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:43:47 by nait-bou          #+#    #+#             */
/*   Updated: 2024/10/07 11:12:21 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incld/minishell.h"

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
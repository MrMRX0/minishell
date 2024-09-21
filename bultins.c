/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultins.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-bou <nait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 09:07:17 by ibougajd          #+#    #+#             */
/*   Updated: 2024/09/21 23:32:58 by nait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	echo(char *str)
// {
// 	if(!str)
// 	{
// 		printf("\n");
// 		return ;
// 	}
	// while(*str)
	// {
	// 	if (*str == '$')
	// 		expand()
	// 	str++;
	// }
// 	printf("%s\n",str);
// }
// void env_(char **env)
// {
// 	int i;

// 	i = 0;
// 	while(env[i])
// 	{
// 		printf("%s\n",env[i]);
// 		i++;
// 	}
// }

char **env_initializer(char **env, char *new_arg) {
    int i = 0;
    char **new_env;

    while (env[i])
        i++;
    int new_size = (new_arg) ? (i + 2) : (i + 1);
    new_env = (char **)malloc(new_size * sizeof(char *));
    if (new_env == NULL) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    for (int j = 0; j < i; j++) {
        new_env[j] = strdup(env[j]);
        if (new_env[j] == NULL) {
            perror("strdup failed");
            exit(EXIT_FAILURE);
        }
    }
    if (new_arg) {
        new_env[i] = strdup(new_arg);
        if (new_env[i] == NULL) {
            perror("strdup failed");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    new_env[i] = NULL;
    return new_env;
}

char	*ft_strjoin_mini(char *s1, char *s2)
{
	char	*all_str;
	int		n;
	int		i;
	int		total_len;

	if (!s2)
		return (NULL);
	if (!s1)
		return(malloc(ft_strlen(s2) * sizeof(char)), strcpy(s1,s2), s1);
	total_len = ft_strlen(s1) + ft_strlen(s2);
	i = -1;
	all_str = (char *)malloc(total_len * sizeof(char) + 1);
	if (!all_str)
		return (NULL);
	while (s1[++i] != '\0')
		all_str[i] = s1[i];
	n = 0;
	while (s2[n])
	{
		all_str[i] = s2[n];
		i++;
		n++;
	}
	all_str[i] = '\0';
	return (all_str);
}

		// if (strcmp(argv[0], "echo") == 0)
		// {
		// 	echo(argv[1]);
		// 	continue;
		// }
		// else if (strcmp(argv[0], "env") == 0)
		// {
		// 	env_(new_env);
		// 	continue;
		// }
		// else if (strcmp(argv[0], "export") == 0)
		// {
		// 	export(argv);
		// 	continue;
		// }
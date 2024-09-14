/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 06:32:49 by ibougajd          #+#    #+#             */
/*   Updated: 2024/09/13 22:58:15 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_exit(t_data *data)
{
	(void)data;
	printf("syntax Error\n");
	exit(1);
}




void ft_lst_add(t_token **lst) 
{
    if (!*lst) {
        *lst = malloc(sizeof(t_token));
        if (!*lst) {
            perror("malloc failed");
            exit(EXIT_FAILURE);
        }
        (*lst)->arg = NULL;
        (*lst)->next = NULL;
        return;
    }
    t_token *current = *lst;
    while (current->next)
        current = current->next;
    t_token *new_node = malloc(sizeof(t_token));
    if (!new_node) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    new_node->arg = NULL;
    new_node->next = NULL;
    current->next = new_node;
}



char *remove_white_spaces(char *str)
{
	int i = 0;
	while(str[i] == ' ' || str[i] == '	')
			i++;
	return(str + i);
}

// char *command ="           echo 'hello'""'world'           ";



void free_linked_list(t_token **lst)
{
	t_token *tmp = NULL;
	while(*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp);
	}
}


int get_len(t_token *lst)
{
	int i;
	int b;
	
	i = 0;
	b = 0;
	while(lst->arg[i])
	{
		if(lst->arg[i] == '\"' && lst->type == D_QUOTE)
			i++;
		else if(lst->arg[i] == '\'' &&  lst->type == S_QUOTE)
			i++;
		else
		{
			b++;
			i++;
		}
	}
	return(b);
}

void get_copy(char *s1, t_token *lst)
{
	int i;
	int b;

	i = 0;
	b = 0;
	// printf("..%d %s\n", lst->type, lst->arg);
	while(lst->arg[i])
	{
		if(lst->arg[i] == '\"' && lst->type == D_QUOTE)
			i++;
		else if(lst->arg[i] == '\'' && lst->type == S_QUOTE)
			i++;
		else
		{
			s1[b] = lst->arg[i];
			b++;
			i++;
		}
	}
	s1[b] = '\0';
}

char **get_copy_of_token(char **argv, t_token **lst)
{
	(void)argv;
	int len = 0;
	t_token *tmp = *lst;
	while(tmp)
	{
		tmp = tmp->next;
		len++;
	}
	tmp= *lst;
	argv = malloc(len * sizeof(char *) + 1);
	int i = 0;
	while(i < len)
	{
		// printf("len of arg[%d] is %d\n",i,get_len(tmp->arg));
		argv[i] = malloc(get_len(tmp) + 1);
		get_copy(argv[i], tmp);
		// printf("%s\n",argv[i]);
		tmp = tmp->next;
		i++;
		
	}
	argv[i] = NULL;
	return(argv);

}

int handle_redirections_and_pipes(char **argv,t_data *data, char **env)
{
	int fd  = 0;
	int i = 0;
	int b = 0;
	char *pathname;
	char **new_arg;
	t_token *tmp = data->token;
	while(tmp)
	{
		if (tmp->type == SINGLE_REDIRECTION)
		{
			new_arg = malloc(i * sizeof(char *));
			while(b < i)
			{
				new_arg[b] = argv[b];
				b++;
			}
			if (tmp->next->arg)
				fd = open(argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			dup2(fd, STDOUT_FILENO);
			pathname = ft_strjoin("/bin/", argv[0]);
			execve(pathname, new_arg, env);
			perror("Error");
			return(1);
		}
		printf("arg  %s\n",tmp->arg);
		printf("type %d\n",tmp->type);
		tmp = tmp->next;
		i++;
	}
	return(0);
}
void  pipe_own(char **tree)
{
	int i = 0;
	int fd[3];
	pid_t pid;
	while (tree[i])
	{
		pipe(fd);
		dup2(fd[0], STDOUT_FILENO);
		dup2(fd[1], STDIN_FILENO);
		execute(tree[i]);
		i++;
		continue;
	}
	dup2(STDOUT_FILENO, fd[0]);
	
}
int main(int ac, char **av, char **env)
{
	if (ac != 1)
		return 1;
	(void)av;
	char *input = NULL;
	char *pathname = NULL;
	char **argv = NULL;
	t_data	data;
	while(1)
	{
		if(data.token != NULL)
			free_linked_list(&data.token);
		data.lexer = (t_lexer ){0};
		data.token = (t_token *){0};
		input = readline(COLOR_BOLD_RED "➜  minishell " COLOR_RESET);
		if(comands_formater(input, argv, &data) == 0)
		{
			argv = get_copy_of_token(argv, &(data.token));
			if(data.lexer.dollar)
				expand(argv,env, &data);
			// red = handle_redirections_and_pipes(argv,&data, env);
			// if(red)
			// 	continue;
		}
		else
			continue;
		add_history(input);
		pid_t pid = fork();
		if (pid == 0)
		{

			pathname = ft_strjoin("/bin/", argv[0]);
			execve(pathname, argv, env);
			perror("Error");
		}
		else
		{
			int status;
			
			waitpid(pid,&status, 0);
		}
	}
	
}

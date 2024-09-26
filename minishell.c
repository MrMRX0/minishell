/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-bou <nait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 06:32:49 by ibougajd          #+#    #+#             */
/*   Updated: 2024/09/26 12:19:23 by nait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void fft_exit(t_data *data)
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
		(*lst)->previous = NULL;
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
	new_node->previous = current;
}



char *remove_white_spaces(char *str)
{
	int i = 0;
	while(str[i] == ' ' || str[i] == '	')
			i++;
	if(!str[i])
		return(NULL);
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
	//free lst after
	lst->arg = s1;
}
char **get_copy_of_token_v3(char **argv, t_token **lst)
{
	int len = 0;
	if (!*lst)
		return(NULL);
	t_token *tmp = *lst;
	while(tmp)
	{
		if(tmp->type == HERDOK || tmp->type == SINGLE_REDIRECTION || tmp->type == APPEND_REDIRECTION || tmp->type == INPUT_REDIRECTION)
			tmp = tmp->next->next;
		else
		{
			tmp = tmp->next;
			len++;
		}
	}
	tmp= *lst;
	argv = malloc(len * sizeof(char *) + 1);
	int i = 0;
	while(tmp)
	{
		// printf("len of arg[%d] is %d\n",i,get_len(tmp->arg));
		if(tmp->type == HERDOK || tmp->type == SINGLE_REDIRECTION || tmp->type == APPEND_REDIRECTION || tmp->type == INPUT_REDIRECTION)
			tmp = tmp->next->next;
		else
		{
			argv[i] = malloc(get_len(tmp) + 1);
			get_copy(argv[i], tmp);
			// printf("%s\n",argv[i]);
			tmp = tmp->next;
			i++;
		}
		
	}
	argv[i] = NULL;
	return(argv);

}
char **get_copy_of_token(char **argv, t_token **lst)
{
	(void)argv;
	int len = 0;
	if (!*lst)
		return(NULL);
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
	return(argv);

}
// char	*check_env(t_data *data)
// {
// 		return (NULL);
// }
void	bultins_runner(char **av, t_data *data)
{
	if (ft_strncmp(av[0], "env", 3) == 0)
		ft_env(av, data);
	else if (ft_strncmp(av[0], "export", 6) == 0)
		ft_export(av, data);
	else if (ft_strncmp(av[0], "unset", 5) == 0)
		ft_unset(av, data);
	else if (ft_strncmp(av[0], "pwd", 3) == 0)
		ft_pwd(av);
	else if (ft_strncmp(av[0], "echo", 4) == 0)
		ft_echo(av);
	else if (ft_strncmp(av[0], "cd", 2) == 0)
		ft_cd(av, data);
	else if (ft_strncmp(av[0], "exit", 4) == 0)
		ft_exit(av, data);
}

int 	ft_buitin_check(char **av)
{
	if (ft_strncmp(av[0], "echo", 4) == 0)
	{
		return (0);
	}
	else if (ft_strncmp(av[0], "pwd", 3) == 0)
	{
		return (0);
	}
	else if (ft_strncmp(av[0], "exit", 4) == 0)
	{
		return (0);
	}
	else if (ft_strncmp(av[0], "env", 3) == 0)
	{
		return (0);
	}
	else if (ft_strncmp(av[0], "export", 6) == 0)
	{
		return (0);
	}
	else if (ft_strncmp(av[0], "unset", 6) == 0)
	{
		return (0);
	}
	else if (ft_strncmp(av[0], "cd", 2) == 0)
	{
		return (0);
	}
	return (1);

}

void	execute(char **args, t_data *data)
{
		pid_t pid = fork();
		char *path = NULL;
		if (pid == 0)
		{
			if (ft_buitin_check(args) == 0)
			{
				bultins_runner(args,data);
			}
			else
			{
				// path = check_env(data);
				path = ft_strjoin("/bin/", args[0]);
				execve(path, args, data->env);
				perror("Error");
			}
		}
		else
		{
			int status;
			
			waitpid(pid,&status, 0);
		}
		restore_stdin_stdout(data->std_in, data->std_out);
}
int redirections(t_token **token)
{
	int i = 0;
	t_token *tmp = *token;
	while(tmp)
	{
		if (tmp->type == SINGLE_REDIRECTION)
		{
			i++;
		}
		tmp = tmp->next;
	}
	if(!i)
		return 0;
	int *fd = malloc(i * sizeof(int));
	tmp = *token;
	i = 0;
	while(tmp)
	{
		if (tmp->type == SINGLE_REDIRECTION || tmp->type == APPEND_REDIRECTION)
		{
			if (tmp->type == APPEND_REDIRECTION)
				fd[i] = open(tmp->next->arg, O_WRONLY | O_CREAT | O_APPEND, 0644);
			else
				fd[i] = open(tmp->next->arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			i++;
		}
		tmp = tmp->next;
	}
	while(fd[i])
		i++;
	dup2(fd[i - 1], STDOUT_FILENO);
	close(fd[i - 1]);
	return(0);
}

int get_size_of_tree(t_token **token)
{
	int ret = 0;
	t_token *tmp = *token;
	if(!tmp)
		return 0;
	while(tmp->next)
	{
		if(tmp->type == PIPE)
			ret++;
		tmp = tmp->next;
	}
	return(ret);
}
void piss_off(t_token **lst, int len)
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
char **get_copy_of_token_version_tow(char **argv, t_token **lst)
{
	int len = 0;
	t_token *tmp = *lst;
	while(tmp && tmp->type != PIPE)
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
	piss_off(lst, len);
	return(argv);

}

void	save_stdin_stdout(int *std_in, int *std_out)
{
	*std_in = dup(0);
	*std_out = dup(1);
}

void	restore_stdin_stdout(int std_in, int std_out)
{
	dup2(std_in, 0);
	dup2(std_out, 1);
	close(std_in);
	close(std_out);
}
int herdok(t_token **node)
{
	static int i;
	char s2[2];
	s2[0] = (i + 48);
	s2[1] = '\0';
	const char *filepath = "/tmp/heardok";

	filepath = ft_strjoin(filepath, s2);
	i++;
	int fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1) {
        write(2, "Failed to open file\n", 20);  // Write to stderr if open fails
        return -1;
    }
	char *input = NULL;
	while(1)
	{
		input = readline(">");
		if (!input)
			break;
		if (strcmp(input, (*node)->next->arg) == 0)
			break;
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
	}
	close(fd);
	free(input);
	fd = open(filepath, O_RDONLY);
    if (fd == -1) {
        write(2, "Failed to reopen file\n", 22);
        return -1;
    }
	return(fd);
	// dup2(fd, STDIN_FILENO);
	// close(fd);
}
// void free_node_2(t_token **token, int a, int b)
// {
	// t_token *new = NULL;
	// t_token *tmp = NULL;
	// int i = 0;
	// while((*token))
	// {
		// if ((*token)->type == a || (*token)->type == b)
			// *token = (*token)->next->next;
		// else
		// {
			// ft_lst_add(&new);
			// while(new->next)
			// 	new = new->next;
			// new = *token;
			// *token = (*token)->next;
			// new->next = NULL;
			// if(i == 0)
			// 	new->previous = NULL;
			// i++;
// 		}
// 	}
// 	while(new->previous)
// 		new = new->previous;
// 	*token = new;
// }

void free_node(t_token ** token, int a, int b)
{
	int i = 0;

	t_token *to_free = NULL;
	t_token *last_next = NULL;
	t_token *hold_pointer = NULL;
	while(*token)
	{
		if ((*token)->type == a || (*token)->type == b)
		{
			if ((*token)->previous)
			{
				last_next = (*token)->previous; // ls << a -l << s -a
				last_next->next = NULL; // ls
			}
			to_free = (*token); // << a ls
			(*token) = (*token)->next; // a -la
			free(to_free);
			to_free = (*token); // a -la
			(*token) = (*token)->next; // -la
			if((*token))
				(*token)->previous = NULL; // -la
			free(to_free);
			if((*token) && last_next)
			{
				last_next->next = (*token); // ls -la
				(*token)->previous = last_next;
			}
			if((*token) == NULL)
				break;
		}
		else if((*token) != NULL)
		{
			if(i == 0)
			{
				hold_pointer = (*token); // ls
				(*token) = (*token)->next; // NULL
				// hold_pointer->next = NULL; // ls

			}
			i++;
			if(*token)
				(*token) = (*token)->next;
		}
	}
	(*token) = hold_pointer;
}
void redirect_input(t_token **token)
{
	t_token *tmp = *token;
	int fd = 0;
	int i = 0;
	while(tmp)
	{
		if (tmp->type == HERDOK)
		{
			fd = herdok(&tmp);
			tmp = tmp->next->next;
			i++;
		}
		else if(tmp->type == INPUT_REDIRECTION)
		{
			int fd;
			fd = open(tmp->next->arg, O_RDONLY);
			if (fd == -1)
			{
				perror("file");
				return ;
			}
			dup2(fd, STDIN_FILENO);
			tmp = tmp->next->next;
			i++;
		}
		else if(tmp)
			tmp = tmp->next;

	}
	if(i)
		dup2(fd, STDIN_FILENO);
}

int minishell(t_data	*data, char **env)
{
	char *input ;
				 
	input = NULL;
	memset(data, 0, sizeof(t_data));
	billed_env_list(env, data);
	while(1)
	{
		if(data->token != NULL)
			free_linked_list(&data->token);
		data->lexer = (t_lexer ){0};
		data->token = (t_token *){0};
		input = readline(COLOR_BOLD_RED "➜  minishell " COLOR_RESET);
		if (!input)
			return(printf("exit"), 0);
		add_history(input);
		lexer(input, data);
		data->env = transform_env(data->env_list);
		if(parsing(input, data) == 0)
		{
			save_stdin_stdout(&data->std_in, &data->std_out);
			execution(data);
			restore_stdin_stdout(data->std_in, data->std_out);
			continue;
		}
	}
	return(0);
}
int main(int ac, char **av, char **env)
{
	(void)av;
	t_data	data;

	if (ac != 1)
		return 1;
	memset(&data, 0, sizeof(t_data));
	minishell(&data, env);
	return (0);
	
}

#include "minishell.h"

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
		(*lst)->next_command = 0;
		return;
	}
	t_token *current = *lst;
	while (current->next)
		current = current->next;
	t_token *new_node = malloc(sizeof(t_token));
	if (!new_node)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	new_node->arg = NULL;
	new_node->next = NULL;
	new_node->next_command = 0;
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
void get_copy_v3(char *s1, t_token *lst)
{
	int i;

	i = 0;
	// printf("..%d %s\n", lst->type, lst->arg);
	while(lst->arg[i])
	{
			s1[i] = lst->arg[i];
			i++;
	}
	s1[i] = '\0';
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
	if(!len)
		return NULL;
	tmp= *lst;
	argv = malloc(len * sizeof(char *) + 1);
	int i = 0;
	while(tmp)
	{
		if(tmp->type == HERDOK || tmp->type == SINGLE_REDIRECTION || tmp->type == APPEND_REDIRECTION || tmp->type == INPUT_REDIRECTION)
			tmp = tmp->next->next;
		else
		{
			if(!tmp->arg)
			{
				argv[i] = NULL;
				tmp = tmp->next;
				i++;
			}
			else
			{
				argv[i] = malloc(ft_strlen(tmp->arg) + 1);
				get_copy_v3(argv[i], tmp);
				tmp = tmp->next;
				i++;
			}
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

int check_splited_path(char **splited_path, char *command)
{
	int i;
	char *path;
	char slash[2];

	i = 0;
	slash[0] = '/';
	slash[1] = '\0';
	while(splited_path[i])
	{
		path = ft_strjoin(splited_path[i], slash);
		path = ft_strjoin(path, command);
		if((access(path, X_OK) == 0))
			return(1);
		i++;
	}
	return(0);
}
int check_path(char *command, t_data *data)
{
	char *path;
	char **splited_path;
	int i;

	i = 0;
	path = NULL;
	splited_path = NULL;
	while(data->env[i])
	{
		splited_path = ft_split(data->env[i], '=');
		if(strcmp(splited_path[0], "PATH") == 0)
			break;
		i++;
	}
	if(!data->env[i])
		return(0);
	path = data->env[i];
	free(splited_path[0]);
	free(splited_path[1]);
	free(splited_path);
	splited_path = ft_split(path, ':');
	i = 0;
	i = check_splited_path(splited_path, command);
	return(i);
}
void ft_error(char **cmd, t_data *data)
{
	write(2, cmd[0], ft_strlen(cmd[0]));
	write(2, ": command not found\n", 21);
	data->exit_status = 127;
	exit(data->exit_status);
}
void	execute(char **args, t_data *data)
{
		if (ft_buitin_check(args) == 0)
		{
			bultins_runner(args,data);
			return ;
		}
		pid_t pid = fork();
		char *path = NULL;
		if (pid == 0)
		{
				if (strchr(args[0], '/'))
				{
					if (execve(args[0], args, data->env) == -1)
					{
						write(2, "minishell: ", 12);
						write(2, args[0], ft_strlen(args[0]));
						write(2, ": No such file or directory\n", 29);
						data->exit_status = 127;
						exit(data->exit_status);
					}
				}
				else if(check_path(args[0], data))
				{
					path = ft_strjoin("/bin/", args[0]);
					data->exit_status = 0;
					if (execve(path, args, data->env) == -1)
					{
						perror("Error");
						exit(data->exit_status);
					}
				}
				else
					ft_error(args, data);

			}
		else
		{
			int status;
			
			waitpid(pid,&status, 0);
			if (WIFEXITED(status))
				data->exit_status = WEXITSTATUS(status); // Get the child's exit status
		}
		restore_stdin_stdout(data->std_in, data->std_out);
}
int redirections(t_token **token)
{
	int i = 0;
	t_token *tmp = *token;
	int fd = 0;
	tmp = *token;
	i = 0;
	while(tmp)
	{
		if ((tmp->next) && (tmp->type == SINGLE_REDIRECTION || tmp->type == APPEND_REDIRECTION))
		{
			if (tmp->type == APPEND_REDIRECTION)
				fd  = open(tmp->next->arg, O_WRONLY | O_CREAT | O_APPEND, 0644);
			else
				fd  = open(tmp->next->arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		tmp = tmp->next;
	}
	// dup2(fd , STDOUT_FILENO);
	// close(fd);
	return(fd);
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
char *herdok_expand(char *str, t_data *data)
{
	int b;
	char *returned_str;
	char *final_str;
	char tmp[2];

	b = 0;
	final_str  = NULL;
	returned_str = NULL;
	while(str[b])
	{
		if(str[b] == '$')
		{
			b++;
			returned_str = handle_dollar_sign(str + b, data, &b);
			if(returned_str)
				final_str = ft_strjoin(final_str, returned_str);
		}
		else
		{
			tmp[0] = str[b];
			tmp[1] = '\0';
			final_str = ft_strjoin(final_str, tmp);
			b++;
		}
	}
	return(final_str);
}

char *extraxt_arg(char *arg)
{
	int i = 0;
	int b = 0;
	while(arg[i])
	{
		if (arg[i] == '\'')
			i++;
		else if (arg[i] == '\"')
			i++;
		else
		{
			i++;
			b++;
		}
	}
	i = 0;
	b = 0;
	char *new_arg = malloc((b + 1) * sizeof(char));
	while(arg[i])
	{
		if (arg[i] == '\'')
			i++;
		else if (arg[i] == '\"')
			i++;
		else
		{
			new_arg[b] = arg[i];
			i++;
			b++;
		}
		new_arg[b] = '\0';
	}
	return(new_arg);
}
int heredoc(t_token **node, t_data *data)
{
	if(!(*node)->next)
		return -1;
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
	char *arg = extraxt_arg((*node)->next->arg);
	while(1)
	{
		input = readline(">");
		if (!input)
		{
			printf("minishell: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n",\
			data->prompt_call_times,  (*node)->next->arg);
			break;
		}
		if (ft_strcmp(input, arg) == 0)
			break;
		if ((ft_strchr(input, '$')) && (ft_strchr((*node)->next->arg, '\'') == 0) && (ft_strchr((*node)->next->arg, '\"') == 0))
			input = herdok_expand(input, data);
		if(input)
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
}

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

int  redirect_input(t_token **token, t_data *data)
{
	t_token *tmp = *token;
	int fd = 0;
	int i = 0;
	while(tmp)
	{
		if (tmp->type == HERDOK)
		{
			fd = heredoc(&tmp, data);
			if(fd == -1)
				return(-1);
			tmp = tmp->next->next;
			i++;
		}
		else if(tmp->type == INPUT_REDIRECTION)
		{
			fd = open(tmp->next->arg, O_RDONLY);
			if (fd == -1)
			{
				perror("minishell");
				data->exit_status = 1;
				return -1;
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
	return 0;
}

int minishell(t_data	*data, char **env)
{
	char *input ;
				 
	input = NULL;
	billed_env_list(env, data);
	data->prompt_call_times = 0;
	while(1)
	{
		if(data->token != NULL)
			free_linked_list(&data->token);
		data->lexer = (t_lexer ){0};
		data->token = (t_token *){0};
		input = readline(COLOR_BOLD_RED "➜  minishell " COLOR_RESET);
		data->prompt_call_times ++;
		if (!input)
			return(printf("exit\n"), exit(0), 0);
		add_history(input);
		data->flag = 0;
		data->env = transform_env(data->env_list);
		if(parsing(input, data) == 0)
		{
			if(parser(data) == 1)
				continue;
			save_stdin_stdout(&data->std_in, &data->std_out);
			execution(data);
			restore_stdin_stdout(data->std_in, data->std_out);
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
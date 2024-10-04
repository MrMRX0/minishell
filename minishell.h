/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 06:33:05 by ibougajd          #+#    #+#             */
/*   Updated: 2024/10/03 14:49:13 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

// Regular Colors
# define COLOR_BLACK "\033[0;30m"
# define COLOR_RED "\033[0;31m"
# define COLOR_GREEN "\033[0;32m"
# define COLOR_YELLOW "\033[0;33m"
# define COLOR_BLUE "\033[0;34m"
# define COLOR_MAGENTA "\033[0;35m"
# define COLOR_CYAN "\033[0;36m"
# define COLOR_WHITE "\033[0;37m"

// Bold Colors
# define COLOR_BOLD_BLACK "\033[1;30m"
# define COLOR_BOLD_RED "\033[1;31m"
# define COLOR_BOLD_GREEN "\033[1;32m"
# define COLOR_BOLD_YELLOW "\033[1;33m"
# define COLOR_BOLD_BLUE "\033[1;34m"
# define COLOR_BOLD_MAGENTA "\033[1;35m"
# define COLOR_BOLD_CYAN "\033[1;36m"
# define COLOR_BOLD_WHITE "\033[1;37m"

// Background Colors
# define COLOR_BG_BLACK "\033[0;40m"
# define COLOR_BG_RED "\033[0;41m"
# define COLOR_BG_GREEN "\033[0;42m"
# define COLOR_BG_YELLOW "\033[0;43m"
# define COLOR_BG_BLUE "\033[0;44m"
# define COLOR_BG_MAGENTA "\033[0;45m"
# define COLOR_BG_CYAN "\033[0;46m"
# define COLOR_BG_WHITE "\033[0;47m"

// Reset Color
# define COLOR_RESET "\033[0m"

# define S_QUOTE 1
# define D_QUOTE 2
# define APPEND_REDIRECTION 3
# define SINGLE_REDIRECTION 4
# define PIPE 5
# define INPUT_REDIRECTION 6
# define HERDOK 7
# define HERDOK_INPUT 8

/*env*/
//--------------------env--------------------
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;
//--------------------env--------------------

typedef struct t_lst_1
{
	char			*arg;
	int				num;
	int				next_command;
	int				type;
	struct t_lst_1	*next;
	struct t_lst_1	*previous;
}					t_token;

typedef struct t_lst_0
{
	char			*input;
	t_token			*token;
	char			**args;
	char			**env;      // myne free
	t_env			*env_list; // myne free
	int				type;
	int				std_in;
	int				std_out;
	int				exit_status; // myne
	int				flag;
	int				syntax_error;
	int				prompt_call_times;
	int				shild_signal;
}					t_data;

/*boul*/
//--------------------boul--------------------
typedef enum e_bool
{
	false = 0,
	true = 1
}					t_bool;
//--------------------boul--------------------

/*env*/
//--------------------env--------------------
t_env				*init_env(char **env);
char				**ft_null_env(void);
void				ft_null_helper(char **default_env);
t_env				*create_env_node(const char *env_var);
char				*ft_strndup(const char *s1, size_t n);
void				shlvl_init(t_data *data);
void				billed_env_list(char **env, t_data *data);
char				**transform_env(t_env *env);
void				join_key_value(char *str, char **envp, int i, t_env *tmp);
//--------------------env--------------------

/*export*/
//--------------------export--------------------
t_bool				ft_export(char **av, t_data *data);
t_env				*ft_copy_env(t_env *env);
void				ft_sort_env(t_env *env);
void				print_env(t_env *env);
t_bool				ft_export_check(char **av, int i);
t_bool				is_valid_identifier(char c, int i);
t_bool				is_exported(char *variable, t_data *data);
char				*ft_key(char *variable);
void				update_exported_variable(char *variable, t_data *data);
void				update_value(t_env *tmp, char *variable);
void				add_exported_variable(char *variable, t_data *data);
t_env				*init_new_variable(char *variable, char *key);
void				free_global_tmp(t_env *tmp);
//--------------------export--------------------

/*ft_env*/
//--------------------ft_env--------------------
t_bool				ft_env(char **av, t_data *data);
int					nb_args(char **args);
//--------------------ft_env--------------------

/*ft_unset*/
//--------------------ft_unset--------------------
t_bool				ft_unset(char **av, t_data *data);
void				remove_variable(char *key, t_data *data);
//--------------------ft_unset--------------------

/*ft_pwd*/
//--------------------ft_pwd--------------------
t_bool				ft_pwd(char **av);
//--------------------ft_pwd--------------------

/*ft_echo*/
//--------------------ft_echo--------------------
t_bool				ft_echo(char **av);
int					ft_strncmp_echo(char *str);
//--------------------ft_echo-------------------

/*ft_cd*/
//--------------------ft_cd--------------------
t_bool				ft_cd(char **av, t_data *data);
t_bool				check_cd(char **av, char *old_pwd);
t_bool				check_directory(char *dir);
void				set_env(t_env *env, const char *key, const char *value,
						t_data *data);
char				*get_env_value(t_env *env, const char *key);
void				error(const char *cmd, const char *msg);
void				change_pwd(t_env *envs, const char *old_pwd,
						const char *pwd, t_data *data);
//--------------------ft_cd--------------------

/*sub_lib*/
//--------------------sub_lib--------------------
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strcat(char *dest, const char *src);
int					ft_strcmp(const char *s1, const char *s2);
//--------------------sub_lib--------------------

/*ft_exit*/
//--------------------ft_exit--------------------
t_bool				ft_exit(char **av, t_data *data);
void				ft_exit_helper2(t_data *data, char **av);
void				ft_exit_helper(char **av, t_data *data);
int					ft_isnumber(char *str);
int					nb_count(char **av);
//--------------------ft_exit--------------------

/*free*/
//--------------------free--------------------
void				free_close_all(t_data *data, char **av);
void				free_env(t_env **env);
void				free_av(char **av);
void				ft_free(t_data *data);
void				free_n_lst(t_token **lst, int len);
void				free_linked_list(t_token **lst);
void				free_double_char(char **str);
//--------------------free--------------------

/*signals*/
//--------------------signals--------------------
void				main_signal_handler(void);
void				handler(int signum);
void				middle_exec_signal(t_data *data);
void				exec_handler(int signum);
//--------------------signals--------------------

/*bultins*/
//---------------------------bultins------------------------------
void				bultins_runner(char **av, t_data *data);
int					ft_buitin_check(char **av);
int					bultins(char **args, t_data *data);
//---------------------------bultins------------------------------


//------------------------------------------------------------------------------------------------------------
//############################################################################################################
//------------------------------------------------------------------------------------------------------------

/*minishell*/
//--------------------minishell--------------------
void				save_stdin_stdout(int *std_in, int *std_out);
void				restore_stdin_stdout(int std_in, int std_out);
int					minishell(t_data *data, char **env);
//--------------------minishell--------------------

/*token*/
//--------------------token--------------------
char 				**get_copy_of_token_v1(char **argv, t_token **lst);
char 				**get_copy_of_token_v2(char **argv, t_token **lst);
void				ft_lst_add(t_token **lst);
t_token 			*extract_token(t_token **token);
void 				join_nodes(t_token **token);
char 				*add_command_to_node(char *command, int i, t_data *data);
//--------------------token--------------------

/*redirections*/
//--------------------redirections--------------------
int					redirect_input(t_token **token, t_data *data);
int					redirections(t_token **token, t_data *data);
char 				*handle_redirections(char *command, t_data *data, char c);
//--------------------redirections--------------------

/*expand*/
//--------------------expand--------------------
char 				**expand(char** argv, t_data *data, t_token **token);
char 				*handle_dollar_sign(char *str, t_data *data, int *b);
char				*expander(char *str, t_data *data);
//--------------------expand--------------------

/*pipe*/
//--------------------pipe--------------------
void				pipe_pipe(int n, t_data *data);
//--------------------pipe--------------------

/*utils*/
//--------------------utils--------------------
char 				*extraxt_arg(char *arg);
int					get_size_of_tree(t_token **token);
void 				ft_error(t_data *data, char *arg, char *error ,int exit_status);
int					get_len(t_token *lst);
char 				*get_copy(t_token *lst);
void				get_copy_v3(char *s1, t_token *lst);
char 				*remove_white_spaces(char *str);
int					str_cmp_n(char *str1, char *str2, int n);
//--------------------utils--------------------

/*path*/
//--------------------path--------------------
char					*check_splited_path(char **splited_path, char *command);
char					*check_path(char *command, t_data *data);
//--------------------path--------------------

/*execution*/
//--------------------execution--------------------
void				normal_execution(t_data *data);
void				execution(t_data *data);
void				execute(char **args, t_data *data);
//--------------------execution--------------------

/*parsing*/
//--------------------parsing--------------------
char 				*handle_quote(char *command , t_data *data, char c);
void				ft_syntax_error(t_data *data);
char				*handle_pipe(char *command, t_data *data);
int					parser(t_data *data);
int					parsing(char *command, t_data *data);
//--------------------parsing--------------------

/*heredoc*/
//--------------------heredoc--------------------
int					heredoc(t_token **node, t_data *data);
char				*herdok_expand(char *str, t_data *data);
void 				set_heredoc_input_value(t_token **token);
//--------------------heredoc--------------------

char *readline_dyali();
#endif
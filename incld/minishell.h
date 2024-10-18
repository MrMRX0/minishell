/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 06:33:05 by ibougajd          #+#    #+#             */
/*   Updated: 2024/10/14 01:55:13 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "../libft/libft.h"
# include "collors.h"

# define S_QUOTE 1
# define D_QUOTE 2
# define A_R 3
# define S_R 4
# define PIPE 5
# define I_R 6
# define HERDOK 7
# define HERDOK_INPUT 8

# define P_D ": Permission denied\n"
# define NO_F_D ": No such file or directory\n"
# define HEREDOC_ERROR \
	"minishell: warning: \
	here-document at line %d delimited by end-of-file (wanted `%s')\n"

typedef struct s_cool
{
	void			*content;
	struct s_cool	*next;
	struct s_cool	*prev;
}					t_cool;

/*env*/
//--------------------env--------------------
typedef struct s_env
{
	char			*key;
	char			*value;
	int				q;
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
	int				is_splited;
}					t_token;

typedef struct t_lst_0
{
	char			*input;
	t_token			*token;
	t_token			*copy;
	char			**args;
	char			**env;
	t_env			*env_list;
	int				type;
	int				std_in;
	int				std_out;
	int				exit_status;
	int				flag;
	int				syntax_error;
	int				prompt_call_times;
	int				shild_signal;
	int				sig_flag;
	int				sig_flag2;
	int				sig_flag3;
	int				tmp_heredoc_flag;
	int				expand_flag;
	int				tmp_error_flag;
	t_cool			*garn;

}					t_data;

typedef struct t_lst_5
{
	int				cmd_idx;
	int				std_out;
	int				std_in;
	char			**command;
	int				*fd;
}					t_pipex;

extern t_data		*g_global_data;

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
t_env				*set_node(t_env *tmp);
void				swap_env(t_env *tmp, t_env *tmp2);
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
t_bool				ft_cd(char **av);
t_bool				check_cd(char **av, char *old_pwd);
t_bool				check_directory(char *dir);
void				set_env(t_env *env, const char *key, const char *value);
char				*get_env_value(t_env *env, const char *key);
void				error(const char *cmd, const char *msg);
void				change_pwd(t_env *envs, const char *old_pwd,
						const char *pwd);
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
void				ft_exit_helper2(char **av);
void				ft_exit_helper(t_data *data);
int					ft_isnumber(char *str);
int					nb_count(char **av);
//--------------------ft_exit--------------------

/*free*/
//--------------------free--------------------
void				free_close_all(t_data *data, char **av);
void				free_env(t_env *env);
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
void				handler_3(int signum);
void				handler_2(int signum);
void				signal_handler_heredoc(void);
void				handler_heredoc(int signum);
//--------------------signals--------------------

/*bultins*/
//---------------------------bultins------------------------------
t_bool				bultins_runner(char **av, t_data *data);
int					ft_buitin_check(char **av);
int					bultins(char **args, t_data *data);
//---------------------------bultins------------------------------

//-----------------------------------------------------------------------------
//#############################################################################
//-----------------------------------------------------------------------------

/*minishell*/
//--------------------minishell--------------------
void				save_stdin_stdout(int *std_in, int *std_out);
void				restore_stdin_stdout(int std_in, int std_out);
int					minishell(t_data *data, char **env);
//--------------------minishell--------------------

/*token*/
//--------------------token--------------------
char				**get_copy_of_token_v1(char **argv, t_token **lst);
char				**get_copy_of_token_v2(char **argv, t_token **lst);
void				ft_lst_add(t_token **lst);
t_token				*extract_token(t_token **token);
void				join_nodes(t_token **token);
char				*add_command_to_node(char *command, int i, t_data *data);
t_token				*copy_token_list(t_token *head);
//--------------------token--------------------

/*redirections*/
//--------------------redirections--------------------
int					redirect_input(t_token **token, t_data *data);
int					redirections(t_token **token, t_data *data);
char				*handle_redirections(char *command, t_data *data, char c);
//--------------------redirections--------------------

/*expand*/
//--------------------expand--------------------
char				**expand(char **argv, t_data *data, t_token **token);
char				*expander(char *str, t_data *data);
char				*get_value(char **env, char *str, int i);
char				*handle_dollar_sign(char *str, t_data *data, int *b);
int					find_dollar_sign(char *str, t_token *tmp);
char				*get_last_res(char *str, t_data *data, int *b,
						char *final_str);
int					ccount_words(const char *s, char c);
char				*gget_next_word(const char **s, char c);
//--------------------expand--------------------

/*expand_utils*/
//--------------------expand_utils--------------------
int					find_dollar_sign(char *str, t_token *tmp);
char				*get_value(char **env, char *str, int i);
char				*handle_dollar_sign(char *str, t_data *data, int *b);
char				*get_last_res(char *str, t_data *data, int *b,
						char *final_str);
char				**ft_split_with_tabs(char const *s, char c);
char				*expander(char *str, t_data *data);
int					get_size_of_double_array(char **arr);
void				get_the_size_of_splited_arr(t_token *tmp, char *final_str);
int					count_dollars(char **argv, t_token *token);
int					get_total_len(t_token *token);
void				not_z(t_token *tmp, t_token **new, char *str);
void				avec_z(t_token **new, char *str);
//--------------------expand_utils--------------------

/*pipex*/
//--------------------pipex--------------------
pid_t				ft_fork(t_pipex *pipe, t_data *data, int n);
void				pipex_child(t_pipex *pipe, t_data *data, int n);
void				pipex(t_data *data, int n);
int					*create_pipes(int n);
//--------------------pipex--------------------

/*pipex_utils*/
//--------------------pipex_utils--------------------
void				close_fds(int n, int *fd);
char				**get_command(t_data *data, int *std_in, int *std_out);
//--------------------pipex_utils--------------------

/*utils*/
//--------------------utils--------------------
char				*extraxt_arg(char *arg);
int					get_size_of_tree(t_token **token);
void				ft_error(t_data *data, char *arg, char *error,
						int exit_status);
int					get_len(t_token *lst);
char				*get_copy(t_token *lst, int flag);
void				get_copy_v3(char *s1, t_token *lst);
char				*remove_white_spaces(char *str);
int					str_cmp_n(char *str1, char *str2, int n);
//--------------------utils--------------------

/*path*/
//--------------------path--------------------
char				*check_splited_path(char **splited_path, char *command);
char				*check_path(char *command, t_data *data);
//--------------------path--------------------

/*execution*/
//--------------------execution--------------------
void				normal_execution(t_data *data);
void				execution(t_data *data);
void				execute(char **args, t_data *data);
//--------------------execution--------------------

/*parsing*/
//--------------------parsing--------------------
int					parser(t_data *data);
int					parsing(char *command, t_data *data);
char				*split_the_command(char *command, int i, t_data *data);
//--------------------parsing--------------------

/*parsing_utils*/
//--------------------parsing_utils--------------------
char				*func2(t_data *data, char *command, char c);
char				*func3(t_data *data, char *command, char c, int i);
char				*func1(t_data *data, char *command, char c);
//--------------------parsing_utils--------------------

/*parsing_utils_2*/
//--------------------parsing_utils_2--------------------
char				*handle_quote(char *command, t_data *data, char c);
void				ft_syntax_error(t_data *data);
char				*handle_pipe(char *command, t_data *data);
//--------------------parsing_utils_2--------------------

/*heredoc*/
//--------------------heredoc--------------------
int					heredoc(t_token **node, t_data *data);
char				*herdok_expand(char *str, t_data *data);
void				set_heredoc_input_value(t_token **token);
//--------------------heredoc--------------------

char				*readline_dyali(void);

void				*ft_malloc(size_t size);
void				ft_free_all(void);
t_cool				**get_heap(void);
void				fft_lstdel_node(t_cool **lst, void (*del)(void *),
						t_cool *node);
t_cool				*fft_lstnew(void *content);
t_bool				fft_lstadd_back(t_cool **lst, t_cool *new);
t_cool				*fft_lstlast(t_cool *lst);
t_bool				fft_lstclear(t_cool **lst, void (*del)(void *));
#endif
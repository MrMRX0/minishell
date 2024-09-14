/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 06:33:05 by ibougajd          #+#    #+#             */
/*   Updated: 2024/09/13 21:33:37 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//set a flag in the free function and increment the flag each time you allocate something
#ifndef MINISHELL_H
#define MINISHELL_H

#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>
#include "libft/libft.h"
#include <linux/limits.h>
#include <fcntl.h>

// Regular Colors
#define COLOR_BLACK     "\033[0;30m"
#define COLOR_RED       "\033[0;31m"
#define COLOR_GREEN     "\033[0;32m"
#define COLOR_YELLOW    "\033[0;33m"
#define COLOR_BLUE      "\033[0;34m"
#define COLOR_MAGENTA   "\033[0;35m"
#define COLOR_CYAN      "\033[0;36m"
#define COLOR_WHITE     "\033[0;37m"

// Bold Colors
#define COLOR_BOLD_BLACK     "\033[1;30m"
#define COLOR_BOLD_RED       "\033[1;31m"
#define COLOR_BOLD_GREEN     "\033[1;32m"
#define COLOR_BOLD_YELLOW    "\033[1;33m"
#define COLOR_BOLD_BLUE      "\033[1;34m"
#define COLOR_BOLD_MAGENTA   "\033[1;35m"
#define COLOR_BOLD_CYAN      "\033[1;36m"
#define COLOR_BOLD_WHITE     "\033[1;37m"

// Background Colors
#define COLOR_BG_BLACK     "\033[0;40m"
#define COLOR_BG_RED       "\033[0;41m"
#define COLOR_BG_GREEN     "\033[0;42m"
#define COLOR_BG_YELLOW    "\033[0;43m"
#define COLOR_BG_BLUE      "\033[0;44m"
#define COLOR_BG_MAGENTA   "\033[0;45m"
#define COLOR_BG_CYAN      "\033[0;46m"
#define COLOR_BG_WHITE     "\033[0;47m"

// Reset Color
#define COLOR_RESET       "\033[0m"

#define S_QUOTE             1
#define D_QUOTE             2
#define APPEND_REDIRECTION  3
#define SINGLE_REDIRECTION  4

typedef struct  t_lst_2
{
    int     single_quote;
    int     double_quote;
    int     dollar;
    int     redirect_input;
    int     redirect_output;
    int     pipe;
}               t_lexer;

typedef struct      t_lst_1
{
    char        *arg;
    int         num;
    int         next_command;
    int         type;
    struct      t_lst_1 *next;
}                   t_token;

typedef struct      t_lst_0
{
    t_lexer     lexer;
    t_token     *token;
    char        **args;
    int         type;
}                   t_data;


void ft_exit(t_data *data);
void ft_lst_add(t_token **lst);
char *remove_white_spaces(char *str);
void free_linked_list(t_token **lst);
void get_copy(char *s1, t_token *lst);
char **get_copy_of_token(char **argv, t_token **lst);
char **env_initializer(char **env, char *new_arg);
char *add_command_to_node(char *command, int i, t_data *data);
char *handle_quote(char *command , t_data *data, char c);
char *handle_redirections(char *command, t_data *data);
char *handle_dollar_sign(char *str, char **env, int *b);
char **expand(char** argv, char**env, t_data *data);
int comands_formater(char *command, char**args, t_data *data);

#endif
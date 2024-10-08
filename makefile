# **************************************************************************** #
#                                   VARIABLES                                  #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS =  -Wall -Wextra  -g 

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS =  main_minishell/minishell.c \
		pipex/pipex.c \
		pipex/pipex_utils.c \
		bultins/buil_tools.c \
		bultins/export_helper.c \
		bultins/ft_export.c \
		bultins/ft_env.c \
		bultins/sib_lib.c \
		bultins/ft_unset.c \
		bultins/ft_pwd.c \
		bultins/ft_echo.c \
		bultins/bultins.c \
		bultins/ft_cd.c \
		bultins/buil_tools1.c \
		bultins/ft_exit.c \
		execution/execution.c \
		execution/path.c \
		parsing/parsing.c \
		parsing/parsing_utils.c \
		parsing/parsing_utils_2.c \
		parsing/parsing_utils_3.c \
		parsing/parsing_utils_4.c \
		parsing/parse_token.c \
		env/env.c	\
		env/env_tools.c \
		free/free.c \
		free/gar_co.c \
		free/utils.c \
		signals/signals.c \
		signals/signals_utils.c \
		redirections/redirections.c \
		redirections/heredoc.c \
		expand/expand.c \
		expand/expand_utils.c \
		main_minishell/ft_readline.c \

OBJS = $(SRCS:.c=.o)


# **************************************************************************** #
#                                 MAKE RULES                                   #
# **************************************************************************** #

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline

# Rule to create object files from .c files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -C $(LIBFT_DIR)
	rm -f $(OBJS)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

# **************************************************************************** #
#                              ADDITIONAL RULES                                #
# **************************************************************************** #

.PHONY: all clean fclean re

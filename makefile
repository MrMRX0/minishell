# **************************************************************************** #
#                                   VARIABLES                                  #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS =  -Wall -Wextra  -g 

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS =  pipe.c \
		bultins/buil_tools.c \
		bultins/export_helper.c \
		bultins/ft_export.c \
		bultins/ft_env.c \
		bultins/sib_lib.c \
		bultins/ft_unset.c \
		bultins/ft_pwd.c \
		bultins/ft_echo.c \
		bultins/bultins.c \
		execution.c \
		minishell.c \
		parsing.c \
		env/env.c	\
		env/env_tools.c \
		bultins/ft_cd.c \
		bultins/buil_tools1.c \
		bultins/ft_exit.c \
		free/free.c \
		signals/signals.c \
		utils.c \
		token.c \
		redirections.c \
		path.c \
		heredoc.c \
		expand/expand.c

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

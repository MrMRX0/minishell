# **************************************************************************** #
#                                   VARIABLES                                  #
# **************************************************************************** #

NAME = minishell

CC = cc -lreadline
CFLAGS = -Wall -Wextra -g

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS_DIR = ./src
BUILTINS_DIR = ./builtins
ENV_DIR = ./env
PARSING_DIR = ./parsing

SRCS = $(addprefix $(ENV_DIR)/, \
		env.c \
		env_tools.c \
	) \
	parsing.c \
	util.c \
	bultins.c \
	minishell.c

OBJS = $(SRCS:.c=.o)

INCLUDES = -I. -I$(LIBFT_DIR) -I$(ENV_DIR) -I$(PARSING_DIR)

# **************************************************************************** #
#                                 MAKE RULES                                   #
# **************************************************************************** #

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

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

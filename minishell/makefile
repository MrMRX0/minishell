NAME = minishell
CFLAGS = -Wall -Wextra 
CC = cc
SOURSE = minishell.c libft/ft_split.c libft/ft_substr.c  libft/ft_strlen.c libft/ft_strjoin.c libft/ft_strchr.c bultins.c parsing.c

OBJ = $(SOURSE:.c=.o)
all:$(NAME)

$(NAME):$(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lreadline
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re : fclean all


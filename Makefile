CC = gcc
FLAGS = -Wall -Wextra -Werror
NAME = Minishell
SRC = main.c

all: $(NAME)

$(NAME):
	$(CC) $(FLAGS) $(SRC) -o $(NAME) -lreadline

clean: 
	rm -f $(NAME)

fclean: clean 
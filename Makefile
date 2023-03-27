CC = gcc
FLAGS = -Wall -Wextra -Werror
NAME = Minishell
SRC = main.c \
	  parsing/line_token.c \
	  libft/ft_strlen.c \
	  libft/ft_strjoin.c \
	  libft/ft_strchr.c \
	  libft/ft_strncmp.c \
	  libft/ft_strdup.c \
	  libft/ft_strlcat.c \
	  libft/ft_strlcpy.c \
	  libft/ft_strrchr.c \
	  libft/ft_strnstr.c \
	  libft/ft_strtrim.c \
	  libft/ft_substr.c \
	  libft/ft_memset.c \
	  libft/ft_bzero.c \
	  libft/ft_memchr.c \
	  libft/ft_memcmp.c \
	  libft/ft_memccpy.c \
	  libft/ft_calloc.c \
	  libft/ft_isalpha.c \
	  libft/ft_isdigit.c \
	  libft/ft_isalnum.c \
	  libft/ft_isascii.c \
	  libft/ft_isprint.c \
	  libft/ft_toupper.c \
	  libft/ft_tolower.c \
	  libft/ft_atoi.c \
	  libft/ft_putchar_fd.c \
	  libft/ft_putstr_fd.c \
	  libft/ft_putendl_fd.c \
	  libft/ft_putnbr_fd.c \
	  libft/ft_split.c \
	  parsing/ft_cut_cmd.c \
	  parsing/ft_init_list.c \
	  parsing/parsing.c \
	  exec/env.c \
	  exec/one_cmd.c \
	  builtins/pwd.c \
	  builtins/echo.c \
	  builtins/cd.c \
	  builtins/ft_env.c \
	  builtins/exit.c

all: $(NAME)

$(NAME):
	$(CC) $(FLAGS) $(SRC) -o $(NAME) -lreadline -g
	@printf "\e[92;5;118m\n>>> Executable ready\n\e[0m"

clean:
	@printf "\033[00;31m\n>>> Executable removed.\n\033[00m"
	rm -f $(NAME)

fclean: clean 

re : fclean all
CC = gcc
FLAGS = -Wall -Wextra -Werror
NAME = Minishell
_NC=`tput sgr0`
_RED=\033[0;31m
_GREEN=\033[0;32m
_YELLOW=\033[0;33m
_BLUE=\033[0;34m
_PURPLE=\033[0;95m
_CYAN=\033[0;36m
_WHITE=\033[0;37m

SRC = main.c \
	  libft/ft_strlen.c \
	  libft/ft_strjoin.c \
	  libft/ft_strchr.c \
	  libft/ft_strncmp.c \
	  libft/ft_strcmp.c \
	  libft/ft_strdup.c \
	  libft/ft_strlcat.c \
	  libft/ft_strlcpy.c \
	  libft/ft_strrchr.c \
	  libft/ft_strnstr.c \
	  libft/ft_strstr.c \
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
	  parsing/init_env.c \
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
	  exec/getPath.c \
	  exec/one_cmd.c \
	  exec/several_cmd.c \
	  exec/exec.c \
	  builtins/pwd.c \
	  builtins/echo.c \
	  builtins/exit.c \
	  builtins/cd.c \
	  builtins/ft_env.c \
	  builtins/ft_export.c \
	  builtins/ft_unset.c \
	  free/free.c \
	  builtins/exec_builtin.c \
	  redir/init_redir.c \
	  signaux/signal_handler.c \
	  error/gestion.c \
	  init/init_datas.c \
	  redir/init.c \
	  utils/utils.c \
	  redir/redir_pars.c \
	  utils/utils_nd.c \
	  parsing/cut.c \
	  meta/meta.c \
	  exec/new_exec.c \
	  utils/gnl.c \
	  redir/heredoc.c

OBJS = $(SRC:.c=.o)

INCL = minishell.h

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME) -lreadline -g
	@printf "\e[92;5;118m\n>>> Executable ready\n\e[0m"

%.o: %.c $(INCL)
	@$(CC) $(FLAGS) -c $< -o $(<:.c=.o)
	@printf "$(_CYAN)Generating $(NAME) objects...$(_BLUE)%-33.33s\r$(_NC)" $@

clean:
	@rm -f $(OBJS)
	@printf "\033[00;31m>>> objects removed.\n\033[00m"

fclean:	clean
		@rm -rf $(NAME)
		@printf "\033[00;31m>>> executable removed.\n\033[00m"

re : fclean all

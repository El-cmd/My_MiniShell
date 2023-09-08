CC = cc
FLAGS = -Wall -Wextra -Werror
NAME = minishell
_NC=`tput sgr0`
_RED=\033[0;31m
_GREEN=\033[0;32m
_YELLOW=\033[0;33m
_BLUE=\033[0;34m
_PURPLE=\033[0;95m
_CYAN=\033[0;36m
_WHITE=\033[0;37m

LIBFT = libft/libft.a

SRC = main.c \
      parsing/init_env.c \
      parsing/ft_cut_cmd.c \
      parsing/change_pwd.c \
      parsing/ft_splitage.c \
      parsing/ft_init_list.c \
      parsing/parsing.c \
      parsing/ft_cut_quote.c \
      exec/getPath.c \
      exec/exec.c \
      builtins/pwd.c \
      builtins/echo.c \
      builtins/exit.c \
      builtins/cd.c \
      builtins/ft_env.c \
      builtins/ft_export.c \
      builtins/ft_export_sort.c \
      builtins/ft_export_exist.c \
      builtins/ft_unset.c \
      free/free.c \
      free/free_tab.c \
      free/free_list.c \
      builtins/exec_builtin.c \
      redir/init_redir.c \
      signaux/signal_handler.c \
      signaux/signal_exec.c \
      error/gestion.c \
      init/init_datas.c \
      redir/init.c \
      utils/utils.c \
      redir/redir_pars.c \
      utils/utils_nd.c \
      parsing/cut.c \
      meta/meta.c \
      exec/new_exec.c \
      exec/finish.c \
      utils/gnl.c \
      redir/heredoc.c\
      quotes/parse_quote.c \
      parsing/parsing_second.c\
      builtins/echo_second.c \
      parsing/cut_cmd_suite.c \
      ft_split_special/ft_split_special.c \
      ft_split_special/ft_split_squote.c \
      ft_split_special/split_utils.c \
      builtins/export_sort_second.c

OBJS = $(SRC:.c=.o)

INCL = minishell.h

my_all: $(NAME)

$(NAME): $(OBJS)
	@make -s -C libft
	@$(CC) $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline -g
	@printf "\e[92;5;118m\n>>> Executable ready\n\e[0m"

%.o: %.c $(INCL)
	@$(CC) $(FLAGS) -c $< -o $(<:.c=.o) -g
	@printf "$(_CYAN)Generating $(NAME) objects...$(_BLUE)%-33.33s\r$(_NC)" $@

clean:
	@make -s -C libft clean
	@rm -f $(OBJS)
	@printf "\033[00;31m>>> objects removed.\n\033[00m"

fclean: clean
	@rm -rf $(NAME)
	@make -s -C libft fclean
	@printf "\033[00;31m>>> executable removed.\n\033[00m"

re: fclean my_all

.PHONY: my_all clean fclean re

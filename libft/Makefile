CC = gcc
FLAGS = -Wall -Wextra -Werror
NAME = libft.a
_NC=`tput sgr0`
_RED=\033[0;31m
_GREEN=\033[0;32m
_YELLOW=\033[0;33m
_BLUE=\033[0;34m
_PURPLE=\033[0;95m
_CYAN=\033[0;36m
_WHITE=\033[0;37m

SRCS =	ft_isalnum.c \
	ft_isprint.c \
      	ft_isascii.c \
		ft_strcpy.c \
      	ft_strlen.c \
      	ft_isalpha.c \
      	ft_tolower.c \
      	ft_toupper.c \
      	ft_strlcat.c \
		ft_strncpy.c \
		ft_strstr.c \
      	ft_isdigit.c \
      	ft_bzero.c \
      	ft_memset.c \
      	ft_strchr.c \
      	ft_strrchr.c \
      	ft_memchr.c \
      	ft_calloc.c \
      	ft_atoi.c \
      	ft_memcmp.c \
      	ft_strlcpy.c \
      	ft_strncmp.c \
      	ft_strnstr.c \
      	ft_strdup.c \
      	ft_substr.c \
      	ft_strjoin.c \
      	ft_putchar_fd.c \
      	ft_putendl_fd.c \
      	ft_putstr_fd.c \
      	ft_strtrim.c \
      	ft_split.c \
      	ft_itoa.c \
      	ft_putnbr_fd.c \
     	ft_strcmp.c

OBJS = $(SRCS:.c=.o)

CFLAGS = -I.

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

%.o: %.c
	@$(CC) $(FLAGS) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

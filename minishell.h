#ifndef MINISHELL_H
	#define MINISHELL_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include "libft/libft.h"
#define BUFFER_SIZE_MAX 2048

//tokeniser la ligne de commande
typedef struct s_token_cmd
{
	bool outRedirection;
	bool multiOutRedirection;
	bool inRedirection;
	bool multiInRedirection;
	bool appendRedirection;
	bool multiAppendRedirection;
	struct s_token *next;
} t_token_cmd;

//tokeniser le prompt
typedef struct s_token_line
{
	int nb_cmd;
	int nb_pipe;
} t_token_line;


//liste chainée des commandes
typedef struct s_cmd
{
	char *cmd;
	struct s_cmd *next;
} t_cmd;


//Parseur
t_token_line *ft_tk_line(char *line);
char	**ft_init_char(char *line);
void 	push(t_cmd **p, char *line);
void 	print_list(t_cmd *p);
void 	make_list(char **line_second);

#endif
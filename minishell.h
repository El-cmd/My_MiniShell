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


typedef struct s_token_line
{
	int nb_cmd;
	int nb_pipe;
} t_token_line;


t_token_line *ft_tk_line(char *line);

//
////fonction de parsing
//char **ft_split(char const *s, char c);
//char *ft_strjoin(char const *s1, char const *s2);
//char *ft_strtrim(char const *s1, char const *set);
//char *ft_substr(char const *s, unsigned int start, size_t len);
//int ft_strlen(const char *s);
//int ft_strncmp(const char *s1, const char *s2, size_t n);
//char *ft_strdup(const char *s1);
//char *ft_strchr(const char *s, int c);
//
////fonction de tokenisation
//t_token *ft_token(char *line);
//t_token *ft_new_token(char *line);
//void ft_add_token(t_token **token, t_token *new_token);
//void ft_free_token(t_token *token);
//
////fonction de commande
//t_cmd *ft_cmd(t_token *token);
//t_cmd *ft_new_cmd(t_token *token);
//void ft_add_cmd(t_cmd **cmd, t_cmd *new_cmd);
//void ft_free_cmd(t_cmd *cmd);
//
//
////fonction de pipe
//t_pipe *ft_pipe(t_cmd *cmd);
//t_pipe *ft_new_pipe(void);
//void ft_add_pipe(t_pipe **pipe, t_pipe *new_pipe);
//void ft_free_pipe(t_pipe *pipe);
//
////fonction de redirection
//void ft_redirection(t_cmd *cmd);
//
////fonction de execution
//
//void ft_exec(t_cmd *cmd, t_pipe *pipe);
//
////fonction de free
//void ft_free(char **str);
//
//
//

#endif
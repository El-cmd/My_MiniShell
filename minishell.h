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


//environnement
typedef struct s_env
{
	char *name;
	struct s_env *next;
	struct s_env *back;
} t_env;

typedef struct s_envSom
{
	int size;
	struct s_env *begin;
	struct s_env *end;
} t_envSom;

//tokeniser la ligne de commande
typedef struct s_token_cmd
{
	int outRedirection;
	int inRedirection;
	int appendRedirection;
	int HereDoc;
	struct s_token_cmd *next;
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
	char **redir;
	struct s_cmd *next;
} t_cmd;


//Parseur
t_token_line *ft_tk_line(char *line);
char	**ft_init_char(char *line);
void 	push(t_cmd **p, char *line);
void 	print_list(t_cmd *p);
void 	make_list(char **line_second, t_token_line *tk_line, char **envp, t_envSom *doberman);
void 	token(t_token_cmd *cmd, t_cmd *cmds);
char	**ft_parsing(t_envSom *env);

//Executer
void	simple_cmd(t_token_cmd *tk_cmd, t_token_line *tk_line, t_envSom *env, t_cmd *cmds, char **envp);
int		ft_builtins(t_cmd *cmd, t_envSom *env);

//Builtins
int		ft_env(t_envSom *env);
int		ft_pwd(void);
void	ft_cd(t_cmd *cmd, t_envSom *env);
int		ft_echo(t_cmd *cmd);
void	ft_exit(void);
int		ft_export(t_envSom *env, t_cmd *cmd);
int 	ft_unset(t_envSom *env, t_cmd *cmd);

//env
t_envSom *init_envp(char **envp);
void	change_pwd(t_envSom *env);
void	change_oldpwd(t_envSom *env, char *oldpwd);
int 	have_olpwd(char **envp);
void	push_env(char *envp, t_envSom *som);

#endif
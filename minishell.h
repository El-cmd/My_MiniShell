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

#define HERD 7
#define APPEND 6
#define R_IN 5
#define R_OUT 4
#define IN 1
#define OUT 0
#define ERR 2
#define BUFFER_SIZE_MAX 2048


//environnement
typedef struct s_env
{
	char *name;
	struct s_env *next;
	struct s_env *back;
} t_env;

//Index environnement
typedef struct s_envSom
{
	int size;
	struct s_env *begin;
	struct s_env *end;
} t_envSom;

//index commande
typedef struct s_cmdIndex
{
	int nb_cmd;
	int nb_pipe;
	struct s_cmd *begin;
	struct s_cmd *end;
} t_cmdIndex;

//liste chainée des commandes
typedef struct s_cmd
{
	char *cmd;
	struct s_cmd *next;
	struct s_cmd *back;
} t_cmd;

//index redirections
typedef struct s_redirIndex
{
	int size;
	struct t_redir *begin;
	struct t_redir *end;
} t_redirIndex;

//liste chainée des redirections
typedef struct s_redir
{
	int type;
	char *file;
	struct s_redir *next;
	struct s_redir *back;
} t_redir;

//init liste cmd
int			ft_pipeError(char *line);
void		pushback_cmd(char *cmd, t_cmdIndex *cmdIndex);
t_cmdIndex *init_cmd(void);
void		splitOrNot(char *line, t_cmdIndex *cmdIndex);

//Parseur
char	**ft_getpath(t_envSom *env);

//Executer
int		simple_cmd(t_envSom *env, t_cmd *cmd, char **envp, t_cmdIndex *cmdIndex);
void 	multi_pipe(t_cmdIndex *index, char **envp, t_envSom *env);
void 	exec(t_cmdIndex *cmd, char **envp, t_envSom *doberman);
void 	ft_execve(char *cmd, char **envp);

//pipe
void	ft_simple_pipe(t_cmdIndex *index, char **envp, t_envSom *env);

//Builtins
int		ft_builtins(t_cmd *cmd, t_envSom *env);
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

//utils
void 	print_list(t_cmdIndex *cmdIndex);
void    printTitle(void);

//free
void	free_list(t_cmdIndex *index);
void	free_tab(char **str);

#endif
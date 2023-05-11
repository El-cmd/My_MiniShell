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

#define HERD 7 // <<
#define APPEND 6 // >>
#define R_IN 5 // <
#define R_OUT 4 // > 
#define IN 1
#define OUT 0
#define ERR 2
#define BUFFER_SIZE_MAX 2048
#define ERROR_TOKEN "minishell: syntax error near unexpected token `newline'\n"

/* piping cmd */
typedef struct s_pipex
{
	char			*herd;
	char			*append;
	char			*r_in;
	char			*r_out;
	char			*in;
	char			*out;
	char			*err;
	char			*cmd;
	int				rd_in;
	int				wr_out;
	int				pos;
	struct s_pipex	*next;
}	t_pipe_cmd;

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
	bool redir;
	struct s_redirIndex *lredir;
	struct s_cmd *next;
	struct s_cmd *back;
	t_pipe_cmd	*p_cmd;
} t_cmd;

//index redirections
typedef struct s_redirIndex
{
	int size;
	struct s_redir *begin;
	struct s_redir *end;
} t_redirIndex;

//liste chainée des redirections
typedef struct s_redir
{
	int type;
	char *file;
	int fd;
	int	begin;
	int len;
	struct s_redir *next;
	struct s_redir *back;
} t_redir;


//datas
typedef struct s_data
{
	char **argv;
	char **envp;
	t_envSom *env;
	t_cmdIndex *cmdIndex;
	char	**path_exec;
} t_data;

/* BUILTINS */
/* cd.c */
int 	settings_cd(t_cmd *cmd);
void	ft_cd(t_cmd *cmd, t_envSom *env);

/* echo.c */
int		ft_echo_n(char *str, t_cmd *cmd);
int		ft_echo(t_cmd *cmd);

/* exec_builtin.c */
int		ft_builtins(t_cmd *cmd, t_envSom *env);

/* exit.c */
void	ft_exit(void);

/* ft_env.c */
int 	ft_env(t_envSom *env);
int 	have_olpwd(char **envp);

/* ft_export.c */
int 	ft_export(t_envSom *env, t_cmd *cmd);

/* ft_unset.c */
int 	search_egal(char *str);
int 	ft_unset(t_envSom *env, t_cmd *cmd);

/* pwd.c */
int		ft_pwd(void);

/* ERROR */
/* gestion.c */
void	the_arg(int ac, char **av);
int		malloc_error(char *str);
pid_t	fork_error(void);

/* EXEC */
/* exec.c */
//void 	exec(t_cmdIndex *cmd, char **envp, t_envSom *doberman);
void 	exec(t_data *data);
void 	ft_execve(char *cmd, char **envp);

/* getPath.c */
char	**ft_getpath(t_envSom *env);

/* one_cmd.c */
int		simple_cmd(t_envSom *env, t_cmd *cmd, char **envp, t_cmdIndex *cmdIndex);

/* several_cmd.c */
void	ft_pipex(t_cmdIndex *index, char **argv, char **envp);

void	ft_simple_pipe(t_cmdIndex *index, char **envp, t_envSom *env);
void	multi_pipe(t_cmdIndex *index, char **envp, t_envSom *env);
void	ft_multi_pipe(t_cmd *cmd, char **envp, t_envSom *env, int *status2);
void	ft_child(t_cmd *cmd, char **envp, t_envSom *env, int fd[2]);
void	ft_parent(int pid, int *status, int fd[2]);
/* FREE */
/* free.c */
t_cmd 	*pop_front_dlist(t_cmdIndex *index);
void	free_list(t_cmdIndex *index);
void	free_tab(char **str);

/* INIT */
/* init_datdas.c */
void	init_data(t_data *data, char **av, char **en);
void 	init_data_cmd(t_data *data);

/* PARSING */
/* ft_cut_cmd.c */
int		ft_pipeError(char *line);
void	splitage(char *line, t_cmdIndex *cmdIndex);
void	splitOrNot(char *line, t_cmdIndex *cmdIndex);

/* ft_init_list.c */
t_cmdIndex *init_cmd(void);
void 		pushback_cmd(char *cmd, t_cmdIndex *cmdIndex);
void 		print_list(t_cmdIndex *cmdIndex);

/* init_env.c */
t_envSom	*init_envSom(void);
void		push_env(char *envp, t_envSom *som);
void		change_pwd(t_envSom *env);
void		change_oldpwd(t_envSom *env, char *oldpwd);
t_envSom	*init_envp(char **envp);

/* parsing.c */


/* REDIR */
/* init.c */
void	redirOrNot(t_cmdIndex *index);
void	initRedirOrnot(t_cmdIndex *index);
int 	malloc_out(char *str, int *i, t_redirIndex *tmp);
int 	malloc_in(char *str, int *i, t_redirIndex *tmp);
int 	malloc_redir(t_data *data);

/* init_redir.c */
t_redirIndex	*init_redirI(void);
void			pushback_redir(t_redirIndex *i, int type, int index, char *str);
int 			lookIfRedir(char *line);

/* redir_pars.c */
void	malloc_all(t_data *data);
void    begin_end_file(int i, t_redir *red, char *str);

/* SIGNAUX */
/* signal_handler.c */
void	newline(void);
void	sigint_handler(int sig);
void 	sigquit_handler(int sig);
void	signal_handler(void);

/* UTILS */
/* utils.c */
void	pass_space(char *str, int *i);
int		is_end_redir(char c);
void 	no_str(char *cmd);
void	get_file(char *str, int *i);
void	printTitle(void);

#endif
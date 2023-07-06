/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:24:10 by vloth             #+#    #+#             */
/*   Updated: 2023/05/23 16:47:47 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>
# include "libft/libft.h"

# define HERD 7 // <<
# define APPEND 6 // >>
# define R_IN 5 // <
# define R_OUT 4 // > 
# define IN 0
# define OUT 1
# define ERR 2
# define BUFFER_SIZE_MAX 2048
# define ERROR_TOKEN "minishell: syntax error near unexpected token `newline'\n"
# define HERE_DOC_FILE "/tmp/mini_here_doc_tmp_file"

typedef struct s_here
{
	char	*str;
	int		len;
	int		capacity;
	int		heredoc_fd;
}	t_here;

//global
typedef struct s_global
{
	pid_t	pid;
	int		last_status;
}	t_global;


//environnement
typedef struct s_env
{
	char *name;
	char *value_split;
	char *name_split;
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
	char		*cmd; // si il ny a pas de redirection regarder cette string
	char		*just_cmd; // si il y a des redirection regarder cette string
	bool		is_built;
	char		**argv;
	bool 		quotes;
	bool		redir;
	int			spec_built;
	bool		have_meta;
	struct s_redirIndex *lredir;
	struct s_cmd *next;
	struct s_cmd *back;
	int			in_file;
	int			out_file;
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
	char **envp;
	t_envSom *env;
	t_cmdIndex *cmdIndex;
	char	**path_exec;
	int		exit_return;
	char	*line;
	t_here	here;
} t_data;


/* BUILTINS */
/* cd.c */
int 	settings_cd(t_cmd *cmd);
void	ft_cd(t_cmd *cmd, t_envSom *env, t_data *data);

/* echo.c */
int		ft_echo_n(t_cmd *cmd);
int		ft_echo(t_cmd *cmd, t_data *data);

/* exec_builtin.c */
int		ft_builtins(t_cmd *cmd, t_envSom *env, t_data *data);
void	is_built(t_data *data);
void	spec_built(t_cmd *cmd, t_data * data);
void	spec_built_first(t_data *data);

/* exit.c */
void	ft_exit(t_cmd *cmd, t_data *data);

/* ft_env.c */
int 	ft_env(t_envSom *env, t_data *data);
int 	have_olpwd(char **envp);

/* ft_export.c */
int 	ft_export(t_envSom *env, t_cmd *cmd, t_data *data);

/* ft_unset.c */
int 	search_egal(char *str);
int 	ft_unset(t_envSom *env, t_cmd *cmd, t_data *data);

/* pwd.c */
int		ft_pwd(t_data *data);

/* ERROR */
/* gestion.c */
void	the_arg(int ac, char **av);
int		malloc_error(char *str);
pid_t	fork_error(void);

/* EXEC */
/* exec.c */
void 	exec(t_data *data);
void 	ft_execve(t_cmd *cmd, t_data *data);
int		ft_ft_exec(t_data *data);

/* getPath.c */
char	**ft_getpath(t_envSom *env);


/* FREE */
/* free.c */
t_cmd 	*pop_front_dlist(t_cmdIndex *index);
void	free_list(t_cmdIndex *index);
void	free_tab(char **str);
void data_env(t_data *data);

/* INIT */
/* init_datdas.c */
void	init_data(t_data *data, char **en);
void 	init_data_cmd(t_data *data, char *line);

/* PARSING */
/* ft_cut_cmd.c */
int		ft_pipeError(char *line);
void	splitage(char *line, t_cmdIndex *cmdIndex);
void	splitOrNot(char *line, t_cmdIndex *cmdIndex);

/* cut.c */
void 		cut(t_cmd *cmd, int *i);
void 		exec_find_cmd(t_data *data);

/* ft_init_list.c */
t_cmdIndex *init_cmd(void);
void 		pushback_cmd(char *cmd, t_cmdIndex *cmdIndex, int quote);
void 		print_list(t_cmdIndex *cmdIndex);

/* init_env.c */
t_envSom	*init_envSom(void);
void		push_env(char *envp, t_envSom *som);
void		change_pwd(t_envSom *env);
void		change_oldpwd(t_envSom *env, char *oldpwd);
t_envSom	*init_envp(char **envp);

/* parsing.c */
void cut_arg(t_data *data);
void split_quotes(char *str, t_cmdIndex *cmdIndex);
int count_simple_quote(char *str);
int count_double_quote(char *str);
int    parseur_quotes(char *str, int i, int c);




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
void    redir_fd(t_cmd *cmd);
void 	boucle_redir(t_data *data);

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
int 	no_str(char *cmd);
void	get_file(char *str, int *i);
void	printTitle(void);
int 	is_redir_or_cmd(char c);

//Test
void	wait_all_and_finish(t_data *data, t_cmd *cmds);
void	exit_process(t_data *data, int *fd);
void	parent_process(t_cmd *cmd, int *fd);
int		ft_ft_exec(t_data *data);
void	ft_launch_cmd(t_data *data, t_cmd *cmd, int *fd);
void	child_process(t_data *data, t_cmd *cmd, int *fd);
void	redirect_in_out(t_cmd *cmd, int *fd);
void	ft_create_here_doc(char *delimiter);
int		get_next_line(int fd, char **line);

//meta
void 	is_meta(t_data *data);
int is_meta_second(char *str);
int is_simple_quote(char *str);
int ft_valid_meta(char *str, t_data *data);
char *ft_getenv(char *str, t_data *data);
void	free_list(t_cmdIndex *index);

extern t_global	global;

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldoctor <eldoctor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:24:10 by vloth             #+#    #+#             */
/*   Updated: 2023/09/06 21:40:55 by eldoctor         ###   ########.fr       */
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

//global
typedef struct s_global
{
	pid_t	pid;
}	t_global;

//environnement
typedef struct s_env
{
	char			*name;
	char			*value_split;
	char			*name_split;
	struct s_env	*next;
	struct s_env	*back;
}	t_env;

//
typedef struct s_split
{
	int	start;
	int	in_quotes;
	int	i;
}	t_split;

//Index environnement
typedef struct s_env_som
{
	int				size;
	struct s_env	*begin;
	struct s_env	*end;
}	t_env_som;

//index commande
typedef struct s_cmd_index
{
	int				nb_cmd;
	int				nb_pipe;
	struct s_cmd	*begin;
	struct s_cmd	*end;
}	t_cmd_index;

//liste chainée des commandes
typedef struct s_cmd
{
	char						*cmd;
	char						*just_cmd;
	bool						is_built;
	char						**argv;
	bool						quotes;
	bool						redir;
	int							spec_built;
	bool						have_meta;
	int							in_file;
	int							out_file;
	struct s_redir_index		*lredir;
	struct s_cmd				*next;
	struct s_cmd				*back;
}	t_cmd;

//index redirections
typedef struct s_redir_index
{
	int				size;
	struct s_redir	*begin;
	struct s_redir	*end;
}	t_redirindex;

//liste chainée des redirections
typedef struct s_redir
{
	int				type;
	char			*file;
	int				fd;
	int				begin;
	int				len;
	struct s_redir	*next;
	struct s_redir	*back;
}	t_redir;

//datas
typedef struct s_data
{
	char		**envp;
	int			exit_return;
	t_env_som	*env;
	t_cmd_index	*cmd_index;
	char		**path_exec;
	char		*line;
}	t_data;

/* BUILTINS */
/* cd.c */
int				settings_cd(t_cmd *cmd);
void			ft_cd(t_cmd *cmd, t_env_som *env, t_data *data);

/* echo.c */
void			ft_echo_n(t_cmd *cmd, int i);
void			ft_echo(t_cmd *cmd, t_data *data);
int				echo_quote(t_cmd *cmd);
void			ft_echo_text(char *text);

/* exec_builtin.c */
int				ft_builtins(t_cmd *cmd, t_env_som *env, t_data *data);
void			is_built(t_data *data);
void			spec_built(t_cmd *cmd, t_data *data);
void			spec_built_first(t_data *data);

/* exit.c */
void			ft_exit(t_cmd *cmd, t_data *data);

/* ft_env.c */
int				ft_env(t_env_som *env, t_data *data);
int				have_olpwd(char **envp);

/* ft_export.c */
int				ft_export(t_env_som *env, t_cmd *cmd, t_data *data);
int				have_egal(char *str);
void			remplace(t_env *tmp2, char **tmp, char *str);

/* ft_export_sort.c */
void			recursive_bubble_sort(char **arr, int n, int i, int swap);
void			bubble_sort(char **arr, int n);
void			alloc_fill(t_env_som *env, char ***env_names, int *env_count);
int				already_exist(char *str, t_env_som *env);

/* ft_export_exist.c */
int				already_exist(char *str, t_env_som *env);
int				does_string_exist(char *str, t_env_som *env);
int				process_string(char *str, t_env_som *env);
void			replace_entry(t_env *envNode, char **newValues, char *string);

/* ft_unset.c */
int				search_egal(char *str);
int				ft_unset(t_env_som *env, t_cmd *cmd, t_data *data);

/* pwd.c */
int				ft_pwd(t_cmd *cmd, t_data *data);

/* ERROR */
/* gestion.c */
void			the_arg(int ac, char **av);
int				malloc_error(char *str);
pid_t			fork_error(void);

/* EXEC */
/* exec.c */
void			exec(t_data *data);
void			ft_execve(t_cmd *cmd, t_data *data);
int				ft_ft_exec(t_data *data);

/* finish.c */
void			exit_process(t_data *data, int *fd);

/* getPath.c */
char			**ft_getpath(t_env_som *env);

/* FREE */
/* free.c */
void			data_env(t_data *data);
void			free_everything(t_data *data);
void			free_redir(t_redirindex *redir);
void			free_cmd(t_cmd *cmd);
t_redir			*pop_front_dlist_redir(t_redirindex *redir);

/* free_tab.c */
void			free_tab(char **str);
char			*debug(char *str);

/* free_list.c */
void			free_list(t_cmd_index *index);
void			free_list_second(t_data *data);
t_cmd			*pop_front_dlist(t_cmd_index *index);

/* INIT */
/* init_datdas.c */
void			init_data(t_data *data, char **en);

/* PARSING */
/* ft_cut_cmd.c */
int				check_error(char *line);
int				others_char(char *cmd);
int				split_or_not(char *line, t_cmd_index *cmd_index);

/* ft_cut_cmd.c */
int				is_quote(const char *str);
void			process_arguments(t_cmd *cmd);
void			cut_quote(t_data *data);
int				error(char *line);
int				pipe_quote(char *line, t_cmd_index *index);
int				pipe_cut(char *line, t_cmd_index *index);
void			not_pipe(char *line, t_cmd_index *cmd_index);

/* ft_splitage.c */
int				splitage(char *line, t_cmd_index *cmd_index);

/* cut.c */
void			cut(t_cmd *cmd, int *i);
void			exec_find_cmd(t_data *data);

/* ft_init_list.c */
t_cmd_index		*init_cmd(void);
void			pushback_cmd(char *cmd, t_cmd_index *cmd_index, int quote);
void			print_list(t_cmd_index *cmd_index);

/* init_env.c */
t_env_som		*init_env_som(void);
void			push_env(char *envp, t_env_som *som);
t_env_som		*init_envp(char **envp);

/* change_pwd.c */
void			change_pwd(t_env_som *env);
void			change_oldpwd(t_env_som *env, char *oldpwd);

/* parsing.c */
void			cut_arg(t_data *data);
int				split_quotes(char *str, t_cmd_index *cmd_index);
int				count_simple_quote(char *str);
int				count_double_quote(char *str);
int				parseur_quotes(char *str, int i, int c);
void			cut_quote_second(t_cmd *cmd, int i);
void			fait_le_cafe_second(char **test, int j);
void			do_meta_second(t_data *data, int i, t_cmd *cmd);

/* ft_cafe.c */
char			*fait_le_cafe(char **test, t_data *data);

/* REDIR */
/* init.c */
void			redir_or_not(t_cmd_index *index);
void			init_redir_or_not(t_cmd_index *index);
int				malloc_out(char *str, int *i, t_redirindex *tmp);
int				malloc_in(char *str, int *i, t_redirindex *tmp);
int				malloc_redir(t_data *data);

/* init_redir.c */
t_redirindex	*init_redir_i(void);
void			pushback_redir(t_redirindex *i, int type, int index, char *str);
int				look_if_redir(char *line);

/* redir_pars.c */
void			malloc_all(t_data *data);
void			begin_end_file(int i, t_redir *red, char *str);
void			redir_fd(t_cmd *cmd);
void			boucle_redir(t_data *data);

/* SIGNAUX */
/* signal_handler.c */
void			newline(void);
void			sigint_handler(int sig);
void			sigint_heredoc_handler(void);
void			reset_signal_handlers(void);
void			sig_sbrt(int code);

/* signal_exec.c */
void			hd_on_sigint(int sig);
void			sigquit_handler(int sig);
void			signal_handler(void);
void			sigint_handler_cmd(int sig);

/* UTILS */
/* utils.c */
void			pass_space(char *str, int *i);
int				is_end_redir(char c);
int				no_str(char *cmd);
void			get_file(char *str, int *i);
void			print_title(void);
int				is_redir_or_cmd(char c);

//Test
void			wait_all_and_finish(t_cmd *cmds, t_data *data);
void			exit_process(t_data *data, int *fd);
void			parent_process(t_cmd *cmd, int *fd);
int				ft_ft_exec(t_data *data);
void			ft_launch_cmd(t_data *data, t_cmd *cmd, int *fd);
void			child_process(t_data *data, t_cmd *cmd, int *fd);
void			redirect_in_out(t_cmd *cmd, int *fd);
void			ft_create_here_doc(char *delimiter);
int				get_next_line(int fd, char **line);

//meta
void			is_meta(t_data *data);
int				is_meta_second(char *str);
int				is_simple_quote(char *str);
int				ft_valid_meta(char *str, t_data *data);
char			*ft_getenv(char *str, t_data *data);
void			free_list(t_cmd_index *index);
char			**ft_split_s(char *s, char c);
int				check_quotes(char *line);

extern t_global	g_global;

#endif
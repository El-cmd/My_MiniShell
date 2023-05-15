#include "../minishell.h"

typedef enum s_node_type
{
	OPERATOR,
	COMMAND,
	NULL_NODE,
}	t_node_type;

typedef enum s_node_type
{
	AND,
	OR,
	APPEND_OPERATOR,
	HERE_DOC,
	OUTPUT_REDIRECTION,
	INPUT_REDIRECTION,
	SEMICOLON,
	STRING,
	COMMAND,
	ARG,
	FILE_ID,
	HEREDOC_END,
	NULL_COMMAND,
	NULL_TOKEN,
	NOT_AN_OPERATOR
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*str;
}	t_token;

typedef struct s_redirection
{
	struct s_redirection	*next;
	t_token_type			type;
	bool					ptn_heredoc_err;
	char					*heredoc_string;
	char					*redirection_file;
}	t_redirection;

typedef struct s_command
{
	t_redirection	*redirections;
	bool			is_null;
	bool			errorc;
	char			*name;
	char			**argv;
	char			**env;
	int				argc;
	int				fd_in;
	int				fd_out;
}	t_command;

typedef struct s_node_data
{
	struct s_node_data	*next;
	t_token_type		operator;
	t_node_type			type;
	t_command			command;
	bool				berror;
	int					priority;
}	t_node_data;

typedef struct s_glob
{
	char	**cpy_env;
	int		last_status;
	bool	is_child;
	bool	in_exec;
}	t_glob;

//extern	t_glob	g_mini;

#define PIPE_IN 1
#define PIPE_OUT 0

/* PIPE HANDLING */
int	execute_pipe(t_node_data *data)
{
	int		fd_pipe[2];
	pid_t	pid;
	int		fd_last_pipe_out;

	fd_last_pipe_out = STDIN_FILENO;
	while (data->next)
	{
		fd_last_pipe_out = pipe_with_next_cmd(&data->command, fd_pipe, fd_last_pipe_out);
		data = data->next;
	}
	pid = ft_fork();
	if (pid = 0)
	{
		data->command.fd_in = fd_last_pipe_out;
		execute_command_child(&data->command);
	}
	close_if(fd_last_pipe_out);
	return (wait_all_child(pid));
}

int	pipe_with_next_cmd(t_command *cmd, int fd_pipe[2], int fd_last_pipe_out)
{
	int	pid;

	ft_pipe(fd_pipe, fd_last_pipe_out);
	pid = ft_fork();
	if (pid == 0)
	{
		close(fd_pipe[PIPE_OUT]);
		cmd->fd_in = fd_last_pipe_out;
		cmd->fd_out = fd_pipe[PIPE_IN];
		execute_command_child(cmd);
	}
	else
	{
		close(fd_pipe[PIPE_IN]);
		close_if(fd_last_pipe_out);
		fd_last_pipe_out = fd_pipe[PIPE_OUT];
	}
	return (fd_last_pipe_out);
}

int	wait_all_child(pid_t last_child_pid)
{
	int		status;
	int		last_child_status;
	pid_t	last_wait_pid;

	last_child_status = 0;
	while (1)
	{
		last_wait_pid = waitpid(-1, &status, 0);
		if (last_wait_pid < 0)
			break ;
		else if (last_wait_pid == last_child_pid)
			last_child_pid = get_real_status(status);
	}
	return (last_child_status);
}

int	get_real_status(int status)
{
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFEXITED(status))
	{
		if (WCOREDUMP(status))
			ft_putstr_fd("Aborted: (core dumped)\n", STDERR_FILENO);
		status = WTERMSIG(status) + 128;
	}
	return (status);
}

void	ft_pipe(int fd_pipe[2], int last_fd_pipe_open)
{
	if (pipe(fd_pipe) < 0)
	{
		perror("FATAL ERROR: pipe");
		close_if(last_fd_pipe_open);
		//rl_clear_history();
		//ft_free_all();
		kill(0, SIGKILL);
		exit(1);
	}
}

pid_t	ft_fork()
{
	pid_t	pid;
	
	pid = fork();
	if (pid < 0)
	{
		perror("FATAL ERROR: fork");
		//rl_clear_history();
		//ft_free_all();
		kill(0, SIGKILL);
		exit(1);
	}
	if (pid == 0)
		g_mini.is_child = true;
	return (pid);
}

int	close_if(int fd)
{
	if (fd > 2)
		close(fd);
	return (1);
}

/* EXECUTION */
int	execute_command_child(t_command *cmd)
{
	char	*path;
	int		status;

	status = 0;
	if (cmd->is_null)
		status = execute_null_command(cmd);
	else if (execute_redirection(cmd))
		status = execute_builtin(cmd);
	else
	{
		path = get_path_cmd(cmd->name, g_mini.cpy_env);
		if (!path)
			status = print_error_cmd_not_found(cmd->name);
		else
			ft_exec_in_child(cmd, path);
	}
	close_if(cmd->fd_in);
	close_if(cmd->fd_out);
	//rl_clear_history();
	//ft_free_all();
	exit(status);
}

int	ft_exec_in_child(t_command *cmd, char *path)
{
	int	dup_fd_in;
	int	dup_fd_out;

	dup_fd_in = dup2(cmd->fd_in, STDIN_FILENO);
	close_if(cmd->fd_in);
	dup_fd_out = dup2(cmd->fd_out, STDOUT_FILENO);
	close_if(cmd->fd_out);
	if (dup_fd_in < 0 || dup_fd_out < 0)
		perror("minishell: dup2");
	else
	{
		execve(path, cmd->argv, g_mini.cpy_env);
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(cmd->argv[0]);
	}
	close_if(cmd->fd_in);
	close_if(cmd->fd_out);
	//rl_clear_history();
	//ft_free_all();
	exit(127);
}

int	execute_null_command(t_command *cmd)
{
	if (execute_redirection(cmd) < 0)
		return (1);
	close_if(cmd->fd_in);
	close_if(cmd->fd_out);
	return (0);
}

int	execute_redirection(t_command *cmd)
{
	t_redirection	*redir;

	redir = cmd->redirections;
	while (redir)
	{
		if (redir->type == INPUT_REDIRECTION || redir->type == HERE_DOC)
		{
			close_if(cmd->fd_in);
			cmd->fd_in = execute_in_redirection(redir);
			if (cmd->fd_in < 0)
				return (close_if(cmd->fd_out));
		}
		else if (redir->type == OUTPUT_REDIRECTION
			|| redir->type == APPEND_OPERATOR)
		{
			close_if(cmd->fd_out);
			cmd->fd_out = execute_out_redirection(redir);
			if (cmd->fd_out < 0)
				return (close_if(cmd->fd_in));
		}
		redir = redir->next;
	}
	return (0);
}

int	execute_in_redirection(t_redirection *redir)
{
	int	fd;

	fd = -1;
	if (redir->type == INPUT_REDIRECTION)
		fd = get_fd_input_redirection(redir);
	else if (redir->type == HERE_DOC)
		fd = get_fd_here_doc(redir);
	return (fd);
}

int	execute_out_redirection(t_redirection *redir)
{
	int	fd;

	fd = -1;
	if (redir->type == OUTPUT_REDIRECTION)
		fd = get_fd_output_redirection(redir);
	else if (redir->type == APPEND_OPERATOR)
		fd + get_fd_append_redirection(redir);
	return (fd);
}

int	get_fd_input_redirection(t_redirection *redir)
{
	int	file_fd;

	file_fd = open(redir->redirection_file, O_RDONLY);
	if (file_fd < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(redir->redirection_file);
		return (-1);
	}
	return (file_fd);
}

int	get_fd_here_doc(t_redirection *redir)
{
	int	fd_pipe[2];

	ft_pipe(fd_pipe, 0);
	ft_putstr_fd(redir->heredoc_string, fd_pipe[PIPE_IN]);
	close_if(fd_pipe[PIPE_IN]);
	return (fd_pipe[PIPE_OUT]);

}

int	get_fd_output_redirection(t_redirection *redir)
{
	int	file_fd;

	file_fd = open(redir->redirection_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (file_fd < 0)
	{
		ft_putstr_fd("minishel: ", STDERR_FILENO);
		perror(redir->redirection_file);
		return (-1);
	}
	return (file_fd);
}

int	get_fd_append_redirection(t_redirection *redir)
{
	int	file_fd;

	file_fd = open(redir->redirection_file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (file_fd < 0)
	{
		ft_putstr_fd("minishel: ", STDERR_FILENO);
		perror(redir->redirection_file);
		return (-1);
	}
	return (file_fd);
}

int	execute_builtin(t_command *cmd)
{
	int	status;

	status = exec_builtin_i(cmd, get_builtin_i(cmd->argv[0]));
	close_if(cmd->fd_in);
	close_if(cmd->fd_out);
	return (status);
}

int	exec_builtin_i(t_command *cmd, int i)
{
	if (i == 0)
		return (echo_builtin(*cmd));
	else if (i == 1)
		return (cd_builtin(*cmd));
	else if (i == 2)
		return (pwd_builtin(*cmd));
	else if (i == 3)
		return (export_builtin(*cmd));
	else if (i == 4)
		return (unset_builtin(*cmd));
	else if (i == 5)
		return (env_builtin(*cmd));
	else if (i == 6)
		return (exit_builtin(*cmd));
	return (0);
}

int	get_builtin_i(char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (0);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (2);
	else if (!ft_strcmp(cmd, "export"))
		return (3);
	else if (!ft_strcmp(cmd, "unset"))
		return (4);
	else if (!ft_strcmp(cmd, "env"))
		return (5);
	else if (!ft_strcmp(cmd, "exit"))
		return (6);
	else
		return (-1);
}

char	*get_path_cmd(char *cmd, char **env)
{
	char	*path;
	char	*tmp;
	size_t	i;

	path = NULL;
	if (*cmd && ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	while (*env && ft_strncmp(*env, "PATH", 4))
		env++;
	if (!*env)
		return (NULL);
	env = ft_split(*env + 5, ':');
	i = 0;
	while (*cmd && env[i])
	{
		tmp = ft_strjoin(env[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!access(path, F_OK))
			break ;
		free(path);
		path = NULL;
		i++;
	}
	return (path);
}

/*
int	execute_simple_command(t_command *cmd)
{
	pid_t		pid;
	int			status;
	char		*path;

	if (cmd->is_null)
		return (execute_null_command(cmd));
	if (execute_redirection(cmd))
		return (1);
	if (is_builtin(cmd->name))
		return (execute_builtin(cmd));
	path = get_path_cmd(cmd->name, g_mini.cpy_env);
	if (!path)
		return (print_error_cmd_not_found(cmd->name));
	pid = ft_fork();
	if (pid == 0)
		ft_exec_in_child(cmd, path);
	close_if(cmd->fd_in);
	close_if(cmd->fd_out);
	waitpid(pid, &status, 0);
	return (get_real_status(status));
}
*/

int	print_error_cmd_not_found(char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	return (127);
}

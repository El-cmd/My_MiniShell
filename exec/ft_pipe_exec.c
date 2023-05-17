#include "../minishell.h"

pid_t	ft_fork();
void	ft_pipe(int fd_pipe[2], int last_fd_pipe_open);
int	get_real_status(int status);
int	wait_all_child(pid_t last_child_pid);
int	pipe_with_next_cmd(t_cmd *cmd, int fd_pipe[2], int fd_last_pipe_out, t_data *all_data);
int	execute_pipe(t_data *all_data);
int	execute_command_child(t_cmd *cmd, t_data *all_data);


//t_global	global;

#define PIPE_IN 1
#define PIPE_OUT 0

/* setting the memory for */

void	ft_fill_in_t_command(t_cmd *cmd)
{
	int	i = 0;

	while (cmd->argv[i])
		i++;
	cmd->argc = i;
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	//cmd->is_null = false;
	//cmd->errorc = false;
}

void	print_cmd(t_cmd *cmd)
{
	int	i;

	printf("cmd node @ '%p'\n", cmd);
	printf("\tcmd:'%s', ac:'%d'\n", cmd->cmd, cmd->argc);
	i = -1;
	while (++i < cmd->argc)
		printf("\t\t:'%s'\n", cmd->argv[i]);
	cmd = cmd->next;
}

void	print_node_data(t_data *all_data)
{
	t_cmd	*cmd;
	int		i;

	cmd = all_data->cmdIndex->begin;
	while (cmd)
	{
		printf("cmd node @ '%p'\n", cmd);
		printf("\tcmd:'%s', ac:'%d'\n", cmd->cmd, cmd->argc);
		i = -1;
		while (++i < cmd->argc)
			printf("\t\t:'%s'\n", cmd->argv[i]);
		cmd = cmd->next;
	}
}

void	ft_pipe_exec(t_data *all_data)
{
	t_cmd		*cmd;

	//printf("<< ft_pipe_exec >>\n");

	cmd = all_data->cmdIndex->begin;
	while (cmd)
	{
		ft_fill_in_t_command(cmd);
		cmd = cmd->next;
	}
	//print_node_data(all_data);
	
	//printf("execute_pipe shall start here\n");
	execute_pipe(all_data);
}

/* PIPE HANDLING */
//int	execute_pipe(t_node_data *data)
int	execute_pipe(t_data *all_data)
{
	t_cmd	*cmd;
	int		fd_pipe[2];
	pid_t	pid;
	int		fd_last_pipe_out;

	cmd = all_data->cmdIndex->begin;
	fd_last_pipe_out = STDIN_FILENO;
	while (cmd->next)
	{
		fd_last_pipe_out = pipe_with_next_cmd(cmd, fd_pipe, fd_last_pipe_out, all_data);
		cmd = cmd->next;
	}
	pid = ft_fork();
	if (pid == 0)
	{
		cmd->fd_in = fd_last_pipe_out;
		//execute_command_child(&data->command);
		execute_command_child(cmd, all_data);
	}
	close_if(fd_last_pipe_out);
	return (wait_all_child(pid));
}

//int	pipe_with_next_cmd(t_command *cmd, int fd_pipe[2], int fd_last_pipe_out)
int	pipe_with_next_cmd(t_cmd *cmd, int fd_pipe[2], int fd_last_pipe_out, t_data *all_data)
{
	int	pid;

	ft_pipe(fd_pipe, fd_last_pipe_out);
	pid = ft_fork();
	if (pid == 0)
	{
		close(fd_pipe[PIPE_OUT]);
		cmd->fd_in = fd_last_pipe_out;
		cmd->fd_out = fd_pipe[PIPE_IN];
		//execute_command_child(cmd);
		execute_command_child(cmd, all_data);
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
	/*
	if (pid == 0)
		global.is_child = true;
	*/
	return (pid);
}
/*
int	close_if(int fd)
{
	if (fd > 2)
		close(fd);
	return (1);
}
*/
/* EXECUTION */
int	ft_exec_in_child(t_cmd *cmd, char *path, char **envp);
int	execute_redirection(t_cmd *cmd);

int	execute_in_redirection(t_redir *redir);
int	execute_out_redirection(t_redir *redir);
int	get_fd_input_redirection(t_redir *redir);
int	get_fd_here_doc(t_redir *redir);
int	get_fd_output_redirection(t_redir *redir);
int	get_fd_append_redirection(t_redir *redir);

/* BUILTI EXEC */
int	execute_builtin(t_cmd *cmd, t_data *all_data);
bool	is_builtin(char *cmd);
int	ft_exec_builtins(t_cmd *cmd, t_data *data);

char	*get_path_cmd(char *cmd, char **env);

int	print_error_cmd_not_found(char *cmd);
//int	execute_command_child(t_command *cmd)
int	execute_command_child(t_cmd *cmd, t_data *all_data)
{
	char	*path;
	int		status;

	print_cmd(cmd);
	status = 0;
	if (cmd->redir)
		status = execute_redirection(cmd);
	else if (cmd->is_built)
	{
		//status = execute_builtin(cmd);
		status = execute_builtin(cmd, all_data);
	}
	else
	{
		//path = get_path_cmd(cmd->argv[0], g_mini.cpy_env);
		path = get_path_cmd(cmd->argv[0], all_data->envp);
		if (!path)
			status = print_error_cmd_not_found(cmd->argv[0]);
		else
			ft_exec_in_child(cmd, path, all_data->envp);
	}
	close_if(cmd->fd_in);
	close_if(cmd->fd_out);
	//rl_clear_history();
	//ft_free_all();
	exit(status);
}

int	ft_exec_in_child(t_cmd *cmd, char *path, char **envp)
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
		execve(path, cmd->argv, envp);
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(cmd->argv[0]);
	}
	close_if(cmd->fd_in);
	close_if(cmd->fd_out);
	//rl_clear_history();
	//ft_free_all();
	exit(127);
}

/*
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
	(void)cmd;
	return (0);
}
*/

int	execute_redirection(t_cmd *cmd)
{
	//t_redirection	*redir;
	t_redir	*redir;

	printf("\t<< execute_redirection >>\n");
	redir = cmd->lredir->begin;
	while (redir)
	{
		printf("\t\tredir:\n");
		if (redir->type == R_IN || redir->type == HERD)
		{
			close_if(cmd->fd_in);
			cmd->fd_in = execute_in_redirection(redir);
			if (cmd->fd_in < 0)
				return (close_if(cmd->fd_out));
		}
		else if (redir->type == R_OUT || redir->type == APPEND)
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
//int	execute_in_redirection(t_redirection *redir)
int	execute_in_redirection(t_redir *redir)
{
	int	fd;

	fd = -1;
	if (redir->type == R_IN)
		fd = get_fd_input_redirection(redir);
	else if (redir->type == HERD)
		fd = get_fd_here_doc(redir);
	return (fd);
}

//int	execute_out_redirection(t_redirection *redir)
int	execute_out_redirection(t_redir *redir)
{
	int	fd;

	printf("\t\ttype:'%d'\tfile:'%s'\tfd:'%d'\n", redir->type, redir->file, redir->fd);
	fd = -1;
	if (redir->type == R_OUT)
		fd = get_fd_output_redirection(redir);
	else if (redir->type == APPEND)
		fd = get_fd_append_redirection(redir);
	return (fd);
}

//int	get_fd_input_redirection(t_redirection *redir)
int	get_fd_input_redirection(t_redir *redir)
{
	int	file_fd;

	file_fd = redir->fd;
	//file_fd = open(redir->file, O_RDONLY);
	if (file_fd < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		//perror(redir->redirection_file);
		perror(redir->file);
		return (-1);
	}
	return (file_fd);
}

//int	get_fd_here_doc(t_redirection *redir)
int	get_fd_here_doc(t_redir *redir)
{
	int	fd_pipe[2];

	ft_pipe(fd_pipe, 0);
	//ft_putstr_fd(redir->heredoc_string, fd_pipe[PIPE_IN]);
	ft_putstr_fd(redir->file, fd_pipe[PIPE_IN]);
	close_if(fd_pipe[PIPE_IN]);
	return (fd_pipe[PIPE_OUT]);

}

//int	get_fd_output_redirection(t_redirection *redir)
int	get_fd_output_redirection(t_redir *redir)
{
	int	file_fd;

	file_fd = redir->fd;
	//file_fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (file_fd < 0)
	{
		ft_putstr_fd("minishel: ", STDERR_FILENO);
		//perror(redir->redirection_file);
		perror(redir->file);
		return (-1);
	}
	return (file_fd);
}

//int	get_fd_append_redirection(t_redirection *redir)
int	get_fd_append_redirection(t_redir *redir)
{
	int	file_fd;

	//file_fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	file_fd = redir->fd;
	if (file_fd < 0)
	{
		ft_putstr_fd("minishel: ", STDERR_FILENO);
		//perror(redir->redirection_file);
		perror(redir->file);
		return (-1);
	}
	return (file_fd);
}

/* BUILTI EXEC */
//int	execute_builtin(t_command *cmd)
int	execute_builtin(t_cmd *cmd, t_data *all_data)
{
	int	status;

	printf("\t<< execute_builtin>>\n");
	status = ft_exec_builtins(cmd, all_data);
	close_if(cmd->fd_in);
	close_if(cmd->fd_out);
	return (status);
}

int	ft_exec_builtins(t_cmd *cmd, t_data *data)
{
	if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (ft_env(data->env, data));
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (ft_pwd(data));
	else if (ft_strcmp(cmd->argv[0], "cd") == 0)
	{
		ft_cd(cmd, data->env, data);
		return (0);
	}
	else if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (ft_echo(cmd, data));
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		ft_exit(cmd, data);
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (ft_export(data->env, cmd, data));
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (ft_unset(data->env, cmd, data));
	return 1;
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

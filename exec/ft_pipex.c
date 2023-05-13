#include "../minishell.h"

/* 
typedef struct s_pipex
{
	char	*infile;
	char	*outfile;
	char	**paths;
	int		prev_fd;
	int		pipe_fd[2];
	int		num_commans;
	int		active_cmds;
	char	**commands;
	int		heredoc_fd;
}	t_pipex;
*/

void	ft_multiple_pipes(t_data *data);
void	ft_init_pipex(t_pipex **pipex);
void	ft_preprocess(t_pipex *pipex, t_data *data);
void	ft_preprocess_cmds(t_pipex *pipex, t_data *data);
void	ft_preprocess_get_allpaths(t_pipex *pipex, t_data *data);
char	*ft_find_path_variable(char **envp);
int		ft_add_slashes(char **all_dirs);
void	ft_prepare_pipes(t_pipex *pipex, t_data *data, int i);
void	ft_prepare_first(t_pipex *pipex);
void	ft_prepare_next(t_pipex *pipex);
void	ft_prepare_last(t_pipex *pipex);
int		ft_check_condition_to_execute(t_pipex *pipex);
void	ft_exec_command(t_pipex *pipex, t_data *data, char *command);
void	ft_wait_for_child_processes(t_pipex *pipex);
char	*ft_extract_command_exit(t_pipex *pipex, char *full_cmd);
char	*ft_find_path_exit(t_pipex *pipex, t_data *data, char *full_cmd);

void	ft_error_exit();
void	ft_error();
void	ft_perror_clean_exit(t_pipex *pipex, char *str);
void	ft_error_clean_exit(t_pipex *pipex);
void	ft_clean_exit(t_pipex *pipex);
void	ft_merror_clean_exit(t_pipex *pipex, char *s1, char *s2);
void	ft_merror(char *s1, char *s2);
void	ft_clean_full(t_pipex *pipex);
void	ft_free_2d_array(char **arr);
void	ft_close_fds(t_pipex *pipex);
void	ft_clean_pipex(t_pipex *pipex);
void	ft_free_perror_exit(t_pipex *pipex, char *command);
void	ft_free_perror2_exit(t_pipex *pipex, char *command, char *full_command);

//void ft_pipex(t_cmdIndex *index, char **path_dirs, t_envSom *envp_nodes)
void ft_pipex(t_data *data)
{
	/*
	t_env	*envp_n;
	t_cmd	*cmd;
	t_redir	*rdr;
	char	**path_dirs;
	char	**tmp;
	int		i;

	printf("ft_pipex\n");
	printf("DATA:\n\tenvp:\n");
	tmp = data->envp;
	i = -1;
	while (tmp[++i])
		printf("envp: '%s'\n", tmp[i]);
	tmp = data->path_exec;
	i = -1;
	while (tmp[++i])
		printf("path_exec: '%s'\n", tmp[i]);

	// each t_cmd node holds single command and all its additional attributes/options/redirections 
	cmd = data->cmdIndex->begin;
	printf("\tt_cmdIndex:\tnb_cmd:'%d'\tnb_pipes:'%d'\n", data->cmdIndex->nb_cmd, data->cmdIndex->nb_pipe);
	while (cmd)
	{
		printf("\tt_cmd\n\t\tcmd:'%s', '%s', redir:'%d'\tcmd @ '%p'\n", cmd->cmd, cmd->just_cmd, cmd->redir, cmd);
		if (cmd->redir)
		{
			rdr = cmd->lredir->begin;
			while (rdr)
			{
				printf("\t\tredir:\ttype:'%d', fd:'%d', begin:'%d', len:'%d', file:'%s'\n", rdr->type, rdr->fd, rdr->begin, rdr->len, rdr->file);
				rdr = rdr->next;
			}
		}
		cmd = cmd->next;
	}

	// here each t_env node (en) holds all lines from environment variables env
	envp_n = data->env->begin;
	printf("\tt_envSom\tsize'%d':\n", data->env->size);
	while (envp_n)
	{
		if (ft_strncmp(envp_n->name, "PATH=", 5) == 0)
			printf("env name:\n'%s'\n", envp_n->name);
		envp_n = envp_n->next;
	}

	// here envp holds every directory in PATH env variable, separated by ':' 
	path_dirs = data->path_exec;
	printf("\tchar **envp. PATH:\n");
	i = -1;
	while (path_dirs[++i])
		printf("\t\tenvp:'%s'\n", path_dirs[i]);
	printf("== == == == == ==\n");
	
	*/
	ft_multiple_pipes(data);
}

void	ft_multiple_pipes(t_data *data)
{
	//t_cmdIndex	*index;
	//char		**path_dirs;
	t_pipex		*pipex;
	int			i;

	pipex = NULL;
	ft_init_pipex(&pipex);
	ft_preprocess(pipex, data);
	i = 0;
	while (i < pipex->num_commands)
	{
		ft_prepare_pipes(pipex, data, i);
		if (ft_check_condition_to_execute(pipex) == 1)
		{
			//printf("so far so good\n");
			ft_exec_command(pipex, data, pipex->commands[i]);
			pipex->active_cmds++;
		}
		i++;
	}
	ft_wait_for_child_processes(pipex);
	ft_clean_full(pipex);
}

void	ft_init_pipex(t_pipex **pipex)
{
	t_pipex	*tmp;

	tmp = (t_pipex *)malloc(sizeof(t_pipex));
	if (!tmp)
		ft_error_exit();
	tmp->infile = NULL;
	tmp->outfile = NULL;
	tmp->paths = NULL;
	tmp->prev_fd = -1;
	tmp->pipe_fd[0] = -1;
	tmp->pipe_fd[1] = -1;
	tmp->num_commands = -1;
	tmp->active_cmds = 0;
	tmp->commands = NULL;
	tmp->heredoc_fd = -1;
	*pipex = tmp;
}

/* preprocessing */
void	ft_preprocess(t_pipex *pipex, t_data *data)
{
	ft_preprocess_cmds(pipex, data);
	ft_preprocess_get_allpaths(pipex, data);
}

void	ft_preprocess_cmds(t_pipex *pipex, t_data *data)
{
	char	**commands;
	t_cmd	*cmd;
	int		i;

	cmd = data->cmdIndex->begin;
	commands = (char **)malloc(sizeof(char *) * (data->cmdIndex->nb_cmd + 1));
	// need to free properly in case of error
	if (!commands)
		ft_error_clean_exit(pipex);
	i = -1;
	while (++i < data->cmdIndex->nb_cmd)
		commands[i] = cmd->cmd;
	commands[i] = NULL;
	pipex->commands = commands;
	pipex->num_commands = i;
}

void	ft_preprocess_get_allpaths(t_pipex *pipex, t_data *data)
{
	char	**all_dirs;
	char	*path_variable;
	//int		i;

	path_variable = ft_find_path_variable(data->envp);
	//printf("ft_get_all_path\npath_envp: '%s'\n", path_variable);
	if (path_variable == NULL)
		ft_merror_clean_exit(pipex, "%s\n", "No 'PATH' variable found in env");
	all_dirs = ft_split(ft_strstr(path_variable, "/"), ':');
	if (!all_dirs)
		ft_perror_clean_exit(pipex, "Malloc failure");
	if (ft_add_slashes(all_dirs) == -1)	
	{

		ft_free_2d_array(all_dirs);
		ft_perror_clean_exit(pipex, "Malloc failure");
	}
	/*
	i = -1;
	while (all_dirs[++i])
		printf("all_dirs: '%s'\n", all_dirs[i]);
	*/
	pipex->paths = all_dirs;
}

char	*ft_find_path_variable(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			return (envp[i]);
	return (NULL);
}

int	ft_add_slashes(char **all_dirs)
{
	char	*path;
	int		i;

	i = -1;
	while (all_dirs[++i])
	{
		path = ft_strjoin(all_dirs[i], "/");
		if (!path)
			return (-1);
		free(all_dirs[i]);
		all_dirs[i] = path;
	}
	return (0);
}

/* preparing pipes */
	
void	ft_prepare_pipes(t_pipex *pipex, t_data *data, int i)
{
	(void)data;

	if (i == 0)
		ft_prepare_first(pipex);
	else if (i == data->cmdIndex->nb_cmd - 1)
		ft_prepare_first(pipex);
	else
		ft_prepare_next(pipex);
}	

void	ft_prepare_first(t_pipex *pipex)
{
	int	fd[2];

	fd[0] = -1;
	fd[1] = -1;
	if (pipe(fd) == -1)
		ft_perror_clean_exit(pipex, "Pipe failure");
	pipex->pipe_fd[0] = fd[0];
	pipex->pipe_fd[1] = fd[1];
	pipex->prev_fd = pipex->pipe_fd[0];
}

void	ft_prepare_next(t_pipex *pipex)
{
	int	fd[2];

	fd[0] = -1;
	fd[1] = -1;
	pipex->prev_fd = pipex->pipe_fd[0];
	close(pipex->pipe_fd[1]);
	if (pipe(fd) == -1)
		ft_perror_clean_exit(pipex, "Pipe failure");
	pipex->pipe_fd[0] = fd[0];
	pipex->pipe_fd[1] = fd[1];
}

void	ft_prepare_last(t_pipex *pipex)
{
	close(pipex->pipe_fd[1]);
	pipex->prev_fd = pipex->pipe_fd[0];
	pipex->pipe_fd[0] = -1;
	pipex->pipe_fd[1] = OUT;
}

int	ft_check_condition_to_execute(t_pipex *pipex)
{
	if (pipex->prev_fd != -1)
		return (1);
	return (0);
}

void	ft_exec_command(t_pipex *pipex, t_data *data, char *command)
{
	char	*command_path;
	char	**splitted_command;
	int		pid;
	/*
	int		i;
	char	**dirs;

	dirs = pipex->paths;
	printf("command: '%s'\n", command);
	printf("paths:\n");
	i = -1;
	while (dirs[++i])
		printf("'%s'\n", dirs[i]);
	*/
	pid = fork();
	if (pid < -1)
		ft_perror_clean_exit(pipex, "Fork failure");
	if (pid == 0)
	{
		if (dup2(pipex->prev_fd, IN) == -1)
			ft_perror_clean_exit(pipex, "Dup2 failure in child.");
		if (dup2(pipex->pipe_fd[1], OUT) == -1)
			ft_perror_clean_exit(pipex, "Dup2 failure in child.");
		ft_close_fds(pipex);
		command_path = ft_find_path_exit(pipex, data, command);
		splitted_command = ft_split(command, ' ');
		if (!splitted_command)
			ft_perror_clean_exit(pipex, "Malloc failure");
		if (execve(command_path, splitted_command, NULL) == -1)
			ft_perror_clean_exit(pipex, "Execve failure");
	}
	else
		close(pipex->prev_fd);
}

char	*ft_find_path_exit(t_pipex *pipex, t_data *data, char *full_cmd)
{
	(void)data;
	char	*possible_path;
	char	*cmd_wo_flag; // Command without flag
	int		i;

	cmd_wo_flag = ft_extract_command_exit(pipex, full_cmd);
	i = 0;
	while (pipex->paths[i] && cmd_wo_flag[0] != '\0') // Second one to handle empty commands
	{
		possible_path = ft_strjoin(pipex->paths[i++], cmd_wo_flag);
		if (!possible_path)
			ft_free_perror_exit(pipex, cmd_wo_flag);
		if (access(possible_path, X_OK) == 0)
			return (possible_path);
		free(possible_path);
		if (errno != 2) // errno = 2 is "No such file or directory"
			ft_free_perror2_exit(pipex, cmd_wo_flag, full_cmd);
	}
	if (full_cmd[0] == '\\')
		ft_merror("bash: %s: No such file or directory\n", full_cmd);
	else
		ft_merror("%s: command not found\n", full_cmd);
	return (free(cmd_wo_flag), ft_clean_exit(pipex), NULL);
}

char	*ft_extract_command_exit(t_pipex *pipex, char *full_cmd)
{
	char	*command;
	int		size;
	int		i;

	size = 0;
	while (full_cmd && full_cmd[size] != '\0' && full_cmd[size] != ' ')
		size++;
	command = (char *)malloc(sizeof(char) * (size + 1));
	if (!command)
		ft_perror_clean_exit(pipex, "Malloc failed in child process");
	i = -1;
	while (++i < size)
		command[i] = full_cmd[i];
	command[i] = '\0';
	return (command);
}

void	ft_wait_for_child_processes(t_pipex *pipex)
{
	int	i;
	int	status;

	i = 0;
	while (i < pipex->active_cmds)
	{
		if (wait(&status) == -1)
			ft_perror_clean_exit(pipex, "Wait Failed");
		if (WIFSIGNALED(status) && WTERMSIG(status) != 13)
		{
			ft_putstr_fd("Child was terminated by signal ", 2);
			ft_putnbr_fd(WTERMSIG(status), 2);
			ft_putchar_fd('\n', 2);
		}
		i++;
	}
}

/* error handling */
void	ft_error_exit()
{
	ft_error();
	exit(-1);
}

void	ft_error()
{
	printf("%s\n", strerror(errno));
}

void	ft_perror_clean_exit(t_pipex *pipex, char *str)
{
	perror(str);
	ft_clean_full(pipex);
	exit(-1);
}

void	ft_error_clean_exit(t_pipex *pipex)
{
	ft_error();
	ft_clean_full(pipex);
	exit(-1);
}

void	ft_clean_exit(t_pipex *pipex)
{
	ft_clean_full(pipex);
	exit(-1);
}

void	ft_merror_clean_exit(t_pipex *pipex, char *s1, char *s2)
{
	ft_merror(s1, s2);
	ft_clean_full(pipex);
	exit(-1);
}

void	ft_merror(char *s1, char *s2)
{
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	ft_putchar_fd('\n', 2);
}

void	ft_clean_full(t_pipex *pipex)
{
	ft_close_fds(pipex);
	ft_clean_pipex(pipex);
}

void	ft_free_perror_exit(t_pipex *pipex, char *command)
{
	free(command);
	ft_perror_clean_exit(pipex, "Malloc failed in child process");
}

void	ft_free_perror2_exit(t_pipex *pipex, char *command, char *full_command)
{
	perror(full_command);
	free(command);
	ft_clean_exit(pipex);
}

void	ft_free_2d_array(char **arr)
{
	int	i;

	i = -1;
	if (arr)
	{
		while (arr[++i])
			free(arr[i]);
		free(arr);	
	}
}

void	ft_close_fds(t_pipex *pipex)
{
	if (pipex->prev_fd != -1)
		close(pipex->prev_fd);
	if (pipex->pipe_fd[0] != -1)
		close(pipex->pipe_fd[0]);
	if (pipex->pipe_fd[1] != -1)
		close(pipex->pipe_fd[1]);
}

void	ft_clean_pipex(t_pipex *pipex)
{
	int	i;

	if (!pipex)
		return ;
	if (pipex->commands)
		free(pipex->commands);
	if (pipex->paths)
	{
		i = -1;
		while (pipex->paths[++i])
			free(pipex->paths[i]);
		free(pipex->paths);
	}
	free(pipex);
}

#include "../minishell.h"

/* 
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
*/

void	ft_multiple_pipes(int nb_cmd, t_cmd *cmd_begin, char **envp);
void	set_redirection(t_cmd *cmd);
t_pipe_cmd	*ft_init(t_cmd *cmd, int pos);
void	ft_pipe(t_pipe_cmd *current, t_cmd *cmd, int next_cmd);
void	ft_exec_cmd(t_cmd *cmd, char **envp);
void	ft_path(char *cmd, char **dir_cmd, char **env);
char	*ft_check_bin(char *dir, char *command);
char	**ft_set_dir_cmd_flg(char *dir_cmd, char *cmd);
void	ft_multiple_child_ex(t_cmd *cmd, char **dir_cmd_flg);
char	*ft_file(t_cmd *cmd);
int		ft_first(t_cmd *cmd);
int		ft_last(t_cmd *cmd);
void	ft_free(char **arr);
void	ft_free_struc(t_pipe_cmd *struc);
int		ft_error(char *dir_cmd, t_envSom *env);
void	ft_error_norm(int fd, char *dir_cmd, char *av_cur_pos);


//void ft_pipex(t_cmdIndex *index, char **argv, char **envp)
/* char **envp holds a line from env 'PATH' separated by ':' */
void ft_pipex(t_cmdIndex *index, char **envp, t_envSom *env)
{
	t_env	*en;
	t_cmd	*cmd;
	t_redir	*rdr;
	//int		i;

	en = env->begin;
	cmd = index->begin;
	printf("ft_pipex\n");
	printf("\tt_cmdIndex. nb_cmd:'%d'\tnb_pipes:'%d'\n", index->nb_cmd, index->nb_pipe);
	while (cmd)
	{
		printf("\tt_cmd. cmd:'%s', redir:'%d'\tcmd @ '%p'\n", cmd->cmd, cmd->redir, cmd);
		if (cmd->redir)
		{
			rdr = cmd->lredir->begin;
			while (rdr)
			{
				printf("\t\tredir. type:'%d', fd:'%d', begin:'%d', len:'%d', file:'%s'\n", rdr->type, rdr->fd, rdr->begin, rdr->len, rdr->file);
				rdr = rdr->next;
			}
		}
		cmd = cmd->next;
	}
	/* here each t_env node (en) holds a line from environment variables env */
	printf("\tt_envSom. size:'%d'\n", env->size);
	while (en)
	{
		if (ft_strncmp(en->name, "PATH=", 5) == 0)
			printf("\tenv name:'%s'\n", en->name);
		en = en->next;
	}
	/* here envp holds every directory in PATH env variable, separated by ':' 
	i = -1;
	while (envp[++i])
		printf("\tenvp:'%s'\n", envp[i]);
	*/
	ft_multiple_pipes(index->nb_cmd, index->begin, envp);
}

void	ft_multiple_pipes(int nb_cmd, t_cmd *cmd_begin, char **envp)
{
	t_pipe_cmd	*current;
	t_pipe_cmd	*previous;
	t_cmd		*tmp_cmd;
	int			i;

	tmp_cmd = cmd_begin;
	i = 0;
	current = ft_init(tmp_cmd, 1);
	while (++i < nb_cmd)
	{
		current->cmd = tmp_cmd->cmd; // should be cmd and -flags if available
		if (i != nb_cmd - 1)
			ft_pipe(current, tmp_cmd, i + 1);
		ft_exec_cmd(tmp_cmd, envp);
		if (current->wr_out != 1)
			close(current->wr_out);
		if (current->rd_in != 0)
			close(current->rd_in);
		previous = current;
		current = current->next;
		ft_free_struc(previous);
		tmp_cmd = tmp_cmd->next;
	}
	while (wait(0) > 0)
	{
	}
}

void	ft_exec_cmd(t_cmd *cmd, char **envp)
{
	pid_t		pid;
	t_pipe_cmd	*cur;
	char		*dir_cmd;
	char		**dir_cmd_flg;

	cur = cmd->p_cmd;
	printf("cur. cmd:'%s', rd_in:'%d', wr_out:'%d'\n", cur->cmd, cur->rd_in, cur->wr_out);
	dir_cmd_flg = NULL;
	dir_cmd = NULL;
	ft_path(cur->cmd, &dir_cmd, envp);
	dir_cmd_flg = ft_set_dir_cmd_flg(dir_cmd, cur->cmd);
	pid = fork();
	if (pid == 0)
		ft_multiple_child_ex(cmd, dir_cmd_flg);
	else
		close(cur->wr_out);
	ft_free(dir_cmd_flg);
	return ;
}

void	ft_multiple_child_ex(t_cmd *cmd, char **dir_cmd_flg)
{
	t_pipe_cmd *cur;

	cur = cmd->p_cmd;
	printf("cur rd_in:'%d', wr_out:'%d', cmd:'%s'\n", cur->rd_in, cur->wr_out, cur->cmd);
	dup2(cur->rd_in, 0);
	//close(cur->next->rd_in);
	dup2(cur->wr_out, 1);
	printf("so far so good!\n");
	execve(dir_cmd_flg[0], dir_cmd_flg, NULL);
	//ft_error(dir_cmd_flg[0], env);
	exit(1);
}
/* settin redirection if any 
void	set_redirection(t_cmd *cmd)
{
	t_redir			*tmp;
	int				i;

	tmp = cmd->lredir->begin;
	i = 0;
	while (++i < cmd->lredir->size)
	{
		//printf("t_redir: type:'%d'\tfile:'%s'\tfd:'%d'\n", tmp->type, tmp->file, tmp->fd);
		if (tmp->type == HERD)
			cmd->p_cmd->herd = tmp->file;
		else if (tmp->type == APPEND)
			cmd->p_cmd->append = tmp->file;
		else if (tmp->type == R_IN)
			cmd->p_cmd->r_in = tmp->file;
		else if (tmp->type == R_OUT)
			cmd->p_cmd->r_out = tmp->file;
		else if (tmp->type == IN)
			cmd->p_cmd->in = tmp->file;
		else if (tmp->type == OUT)
			cmd->p_cmd->out = tmp->file;
		else if (tmp->type == ERR)
			cmd->p_cmd->err = tmp->file;
		tmp = tmp->next;
	}
}
*/
t_pipe_cmd	*ft_init(t_cmd *cmd, int pos)
{
	t_pipe_cmd	*tmp;

	tmp = (t_pipe_cmd *)malloc(sizeof(t_pipe_cmd));
	if (!tmp)
	{}
	cmd->p_cmd = tmp; // passing the handle of t_pipe_cmd to t_cmd
	tmp->rd_in = 0;
	tmp->cmd = cmd->cmd;
	tmp->pos = pos; //  this is the cmd sequence while piping
	tmp->wr_out = 1;
	//if (cmd->redir)
	//	set_redirection(cmd);
	return (tmp);
}

void	ft_pipe(t_pipe_cmd *current, t_cmd *cmd, int next_cmd)
{
	int	fd[2];

	current->next = ft_init(cmd, next_cmd);
	pipe(fd);
	current->wr_out = fd[1];
	current->next->rd_in = fd[0];
}

/*
void	ft_exec_cmd(t_cmd *cmd, char **envp, t_envSom *env, int nb_cmd)
{
	pid_t		pid;
	t_pipe_cmd	*cur;
	char		*dir_cmd;
	char		**dir_cmd_flg;

	cur = cmd->p_cmd;
	printf("cur. cmd:'%s', rd_in:'%d', wr_out:'%d'\n", cur->cmd, cur->rd_in, cur->wr_out);
	dir_cmd_flg = NULL;
	dir_cmd = NULL;
	ft_path(cur->cmd, &dir_cmd, envp);
	dir_cmd_flg = ft_set_dir_cmd_flg(dir_cmd, cur->cmd);
	printf("so far so good!\n");
	pid = fork();
	if (pid == 0)
		ft_multiple_child_ex(cmd, env, dir_cmd_flg, nb_cmd);
	ft_free(dir_cmd_flg);
	return ;
}
*/
void	ft_path(char *cmd, char **dir_cmd, char **env)
{
	int		i;
	char	**path_all_dirs;
	char	**command;

	command = ft_split(cmd, ' ');
	i = -1;
	while (command[++i])
		printf("\t\tcommand:'%s'\n", command[i]);
	/*
	while (env && env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	path_all_dirs = ft_split(env[i], ':');
	*/
	path_all_dirs = env;
	i = -1;
	while (path_all_dirs[++i])
		printf("\t\tenvp:'%s'\n", path_all_dirs[i]);
	if (command[0] && command[0][0] == '/' && !(*dir_cmd))
		*dir_cmd = ft_strdup(command[0]);
	else if (path_all_dirs)
	{
		*dir_cmd = ft_check_bin(path_all_dirs[0] + 5, command[0]);
		i = 0;
		while (command[0] && path_all_dirs[i] && *dir_cmd == NULL)
			*dir_cmd = ft_check_bin(path_all_dirs[++i], command[0]);
	}
	else if (*dir_cmd == NULL && !path_all_dirs)
		*dir_cmd = ft_strdup("error");
	ft_free(command);
	//ft_free(path_all_dirs);
}
/*
void	ft_path(char *cmd, char **dir_cmd, char **env)
{
	int		i;
	char	**path_all_dirs;
	char	**command;

	i = 0;
	command = ft_split(cmd, ' ');
	while (env && env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	path_all_dirs = ft_split(env[i], ':');
	if (command[0] && command[0][0] == '/' && !(*dir_cmd))
		*dir_cmd = ft_strdup(command[0]);
	else if (path_all_dirs)
	{
		*dir_cmd = ft_check_bin(path_all_dirs[0] + 5, command[0]);
		i = 0;
		while (command[0] && path_all_dirs[i] && *dir_cmd == NULL)
			*dir_cmd = ft_check_bin(path_all_dirs[++i], command[0]);
	}
	else if (*dir_cmd == NULL && !path_all_dirs)
		*dir_cmd = ft_strdup("error");
	ft_free(command);
	ft_free(path_all_dirs);
}
*/
char	*ft_check_bin(char *dir, char *command)
{
	int		fd;
	char	*dir_cmd;
	char	*tmp;

	tmp = ft_strjoin(dir, "/");
	dir_cmd = ft_strjoin(tmp, command);
	fd = open(dir_cmd, O_RDONLY);
	if (fd == -1)
	{
		free(tmp);
		free(dir_cmd);
		return (NULL);
	}
	close(fd);
	free(tmp);
	return (dir_cmd);
}

char	**ft_set_dir_cmd_flg(char *dir_cmd, char *cmd)
{
	char	**arr;

	if (cmd[0] != '\0')
	{
		arr = ft_split(cmd, ' ');
		free(arr[0]);
		arr[0] = dir_cmd;
	}
	else
	{
		arr = malloc(sizeof (char **) * 1024);
		arr[0] = ft_strdup("err");
	}
	return (arr);
}

/* we probably want to change the conditions 
void	ft_multiple_child_ex(t_cmd *cmd, char **av, char **dir_cmd_flg, int n)
{
	t_pipe_cmd *cur;
	int	ret;

	cur = cmd->p_cmd;
	ret = 0;
	if (cur->pos == 1) // case for the first cmd
		ret = ft_first(cmd);
	if (cur->rd_in != 0 && cur->pos != n && cur->pos != 1)
		dup2(cur->rd_in, 0);
	if (cur->wr_out != 1 && cur->pos != n - 2 && cur->pos != 1)
	{
		close(cur->next->rd_in);
		dup2(cur->wr_out, 1);
		ret = 1;
	}
	else if (cur->pos == n) // case for the last cmd
		ret = ft_last(cmd);
	if (ret == 1)
	{
		execve(dir_cmd_flg[0], dir_cmd_flg, NULL);
		ft_error(dir_cmd_flg[0], av[cur->pos]);
		exit(ret);
	}
	exit(1);
}

void	ft_multiple_child_ex(t_cmd *cmd, t_envSom *env, char **dir_cmd_flg, int n)
{
	t_pipe_cmd *cur;
	int	ret;

	cur = cmd->p_cmd;
	ret = 0;
	if (cur->pos == 1) // case for the first cmd
		ret = ft_first(cmd);
	if (cur->pos <= n)
		dup2(cur->rd_in, 0);
	if (cur->pos <= n)
	{
		close(cur->next->rd_in);
		dup2(cur->wr_out, 1);
		ret = 1;
	}
	else if (cur->pos == n) // case for the last cmd
		ret = ft_last(cmd);
	if (ret == 1)
	{
		execve(dir_cmd_flg[0], dir_cmd_flg, NULL);
		ft_error(dir_cmd_flg[0], env);
		exit(ret);
	}
	exit(1);
}
** to be able to read from and wrtite to a file at command number */

/* check if there redirection file 
char	*ft_file(t_cmd *cmd)
{
	char		*file;
	t_pipe_cmd	*cur;

	cur = cmd->p_cmd;
	file = NULL;
	if (!cmd->redir)
		return (file);
	else if (cur->herd)
		file = cur->herd;
	else if (cur->append)
		file = cur->append;
	else if (cur->r_in)
		file = cur->r_in;
	else if (cur->r_out)
		file = cur->r_out;
	else if (cur->in)
		file = cur->in;
	else if (cur->out)
		file = cur->out;
	else if (cur->err)
		file = cur->err;
	return (file);
}
*/

int	ft_first(t_cmd *cmd)
{
	t_pipe_cmd	*cur;
	//char		*file;
	//int			fd;

	//file = ft_file(cmd);
	cur = cmd->p_cmd;
	/*
	fd = open(file, O_RDONLY); // might need to change the permisions
	if (fd == -1)
	{
		ft_putstr_fd("err: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": No such file or directory \n", 2);
		return (0);
	}
	*/
	//dup2(fd, 0);
	dup2(cur->wr_out, 1);
	//close(fd);
	close(cur->wr_out);
	close(cur->next->rd_in);
	return (1);
}

int	ft_last(t_cmd *cmd)
{
	t_pipe_cmd	*cur;
	//char		*file;
	//int			fd;

	//file = ft_file(cmd);
	cur = cmd->p_cmd;
	/*
	fd = open(file, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("err: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": permisson denied\n", 2);
		return (0);
	}
	*/
	//dup2(fd, 1);
	dup2(cur->rd_in, 0);
	//close(fd);
	close(cur->rd_in);
	return (1);
}

void	ft_free(char **arr)
{
	int	i;

	i = 0;
	if (arr != NULL)
	{
		while (arr[i] && arr[i][0] != '\0')
		{
			free(arr[i++]);
			arr[i - 1] = NULL;
		}
		free(arr);
		arr = NULL;
	}
	return ;
}

void	ft_free_struc(t_pipe_cmd *struc)
{
	if (struc)
	{
		free(struc);
		struc = NULL;
	}
}

int	ft_error(char *dir_cmd, t_envSom *env)
{
	int	fd;
	int	ret;

	fd = open(dir_cmd, O_WRONLY);
	printf("ft_error. fd:'%d'\n", fd);
	printf("t_envSom. size:'%d'\n", env->size);
	//ft_error_norm(fd, dir_cmd, env);
	if ((dir_cmd && ft_strchr(dir_cmd, '/') == NULL) || (fd == -1))
		ret = 127;
	else
		ret = 126;
	close(fd);
	return (ret);
}

/*
void	ft_error_norm(int fd, char *dir_cmd, t_envSom *env)
{
	int	i;
	t_env	*tenv;

	tenv = env->begin;
	i = 0;
	ft_putstr_fd("err: ", 2);
	if (dir_cmd && !(ft_strncmp(dir_cmd, "error", 6)))
	{
		ft_putstr_fd(av_cur_pos, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		i = 1;
	}
	else if (fd == -1)
		dir_cmd = av_cur_pos;
	if (i == 0)
		ft_putstr_fd(dir_cmd, 2);
	if ((ft_strchr(dir_cmd, '/')) == NULL && i == 0)
		ft_putstr_fd(": command not found\n", 2);
	else if (fd == -1 && i == 0)
		ft_putstr_fd(": No such file or directory\n", 2);
	else if (fd == -1 && i == 0)
		ft_putstr_fd(": is a directory\n", 2);
	else if (fd != -1 && i == 0)
		ft_putstr_fd(": Permission denied\n", 2);
}
*/
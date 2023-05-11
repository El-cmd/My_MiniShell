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

void	ft_multiple_pipes(int nb_cmd, t_cmd *cmd_begin, char **av, char **envp);
void	set_redirection(t_cmd *cmd);
t_pipe_cmd	*ft_init(t_cmd *cmd, int pos);
void	ft_pipe(t_pipe_cmd *current, t_cmd *cmd, int next_cmd);
void	ft_exec_cmd(t_cmd *cmd, char **av, char **env, int nb_cmd);
void	ft_path(char *cmd, char **dir_cmd, char **env);
char	*ft_check_bin(char *dir, char *command);
char	**ft_set_dir_cmd_flg(char *dir_cmd, char *cmd);
void	ft_multiple_child_ex(t_cmd *cmd, char **av, char **dir_cmd_flg, int n);
char	*ft_file(t_cmd *cmd);
int		ft_first(t_cmd *cmd);
int		ft_last(t_cmd *cmd);
void	ft_free(char **arr);
void	ft_free_struc(t_pipe_cmd *struc);
int		ft_error(char *dir_cmd, char *av_cur_pos);
void	ft_error_norm(int fd, char *dir_cmd, char *av_cur_pos);


void ft_pipex(t_cmdIndex *index, char **argv, char **envp)
{
	ft_multiple_pipes(index->nb_cmd, index->begin, argv, envp);
}

void	ft_multiple_pipes(int nb_cmd, t_cmd *cmd_begin, char **av, char **envp)
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
		ft_exec_cmd(tmp_cmd, av, envp, nb_cmd);
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

/* settin redirection if any */
void	set_redirection(t_cmd *cmd)
{
	t_redir			*tmp;
	int				i;

	tmp = cmd->lredir->begin;
	i = -1;
	while (++i < cmd->lredir->size)
	{
		if (tmp->type == HERD)
			cmd->p_cmd->herd = tmp->file;
		if (tmp->type == APPEND)
			cmd->p_cmd->append = tmp->file;
		if (tmp->type == R_IN)
			cmd->p_cmd->r_in = tmp->file;
		if (tmp->type == R_OUT)
			cmd->p_cmd->r_out = tmp->file;
		if (tmp->type == IN)
			cmd->p_cmd->in = tmp->file;
		if (tmp->type == OUT)
			cmd->p_cmd->out = tmp->file;
		if (tmp->type == ERR)
			cmd->p_cmd->err = tmp->file;
		tmp = tmp->next;
	}
}

t_pipe_cmd	*ft_init(t_cmd *cmd, int pos)
{
	t_pipe_cmd	*tmp;

	tmp = (t_pipe_cmd *)malloc(sizeof(t_pipe_cmd));
	if (!tmp)
	{}
	cmd->p_cmd = tmp; // passing the handle of t_pipe_cmd to t_cmd
	tmp->herd = NULL;
	tmp->append = NULL;
	tmp->r_in = NULL;
	tmp->r_out = NULL;
	tmp->in = NULL;
	tmp->out = NULL;
	tmp->err = NULL;
	tmp->rd_in = 0;
	//tmp->file_name = file;
	tmp->pos = pos; //  this is the cmd sequence while piping
	tmp->wr_out = 1;
	if (cmd->redir)
		set_redirection(cmd);
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

void	ft_exec_cmd(t_cmd *cmd, char **av, char **env, int nb_cmd)
{
	pid_t		pid;
	t_pipe_cmd	*cur;
	char		*dir_cmd;
	char		**dir_cmd_flg;

	cur = cmd->p_cmd;
	dir_cmd_flg = NULL;
	dir_cmd = NULL;
	ft_path(cur->cmd, &dir_cmd, env);
	dir_cmd_flg = ft_set_dir_cmd_flg(dir_cmd, cur->cmd);
	pid = fork();
	if (pid == 0)
		ft_multiple_child_ex(cmd, av, dir_cmd_flg, nb_cmd);
	ft_free(dir_cmd_flg);
	return ;
}

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
** to be able to read from and wrtite to a file at command number */
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

/* check if there redirection file */
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

int	ft_first(t_cmd *cmd)
{
	t_pipe_cmd	*cur;
	char		*file;
	int			fd;

	file = ft_file(cmd);
	cur = cmd->p_cmd;
	fd = open(file, O_RDONLY); // might need to change the permisions
	if (fd == -1)
	{
		ft_putstr_fd("err: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": No such file or directory \n", 2);
		return (0);
	}
	dup2(fd, 0);
	dup2(cur->wr_out, 1);
	close(fd);
	close(cur->wr_out);
	close(cur->next->rd_in);
	return (1);
}

int	ft_last(t_cmd *cmd)
{
	t_pipe_cmd	*cur;
	char		*file;
	int			fd;

	file = ft_file(cmd);
	cur = cmd->p_cmd;
	fd = open(file, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("err: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": permisson denied\n", 2);
		return (0);
	}
	dup2(fd, 1);
	dup2(cur->rd_in, 0);
	close(fd);
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

int	ft_error(char *dir_cmd, char *av_cur_pos)
{
	int	fd;
	int	ret;

	fd = open(dir_cmd, O_WRONLY);
	ft_error_norm(fd, dir_cmd, av_cur_pos);
	if ((dir_cmd && ft_strchr(dir_cmd, '/') == NULL) || (fd == -1))
		ret = 127;
	else
		ret = 126;
	close(fd);
	return (ret);
}

void	ft_error_norm(int fd, char *dir_cmd, char *av_cur_pos)
{
	int	i;

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

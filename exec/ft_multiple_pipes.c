#include "../minishell.h"

typedef struct s_pipex
{
	char			*file_name;
	char			*cmd;
	int				rd_in;
	int				wr_out;
	int				pos;
	struct s_pipex	*next;
}	t_pipe_cmd;

/* 
void	ft_multiple_pipes(int ac, char **av, char **env);
t_pipe_cmd	*ft_init(int pos, char *file);
void	ft_pipe(t_pipe_cmd *current, int ac, int i, char *file);
void	ft_exec_cmd(t_pipe_cmd *cur, char **av, char **env, int ac);
void	ft_path(char *cmd, char **dir_cmd, char **env);
char	*ft_check_bin(char *dir, char *command);
char	**ft_set_dir_cmd_flg(char *dir_cmd, char *cmd);
void	ft_multiple_child_ex(t_pipe_cmd *cur, char **av, char **dir_cmd_flg, int ac);
int		ft_first(t_pipe_cmd *cur);
int		ft_last(t_pipe_cmd *cur);
void	ft_free(char **arr);
void	ft_free_struc(t_pipe_cmd *struc);
*/

//void	ft_multiple_pipes(int ac, char **av, char **env)
void multi_pipe(t_cmdIndex *index, char **envp, t_envSom *env)
{
	ft_multiple_pipes(index->nb_cmd, index->begin, envp);
}

void	ft_multiple_pipes(int nb_cmd, t_cmd *cmd_begin, char **envp)
{
	t_pipe_cmd	*current;
	t_pipe_cmd	*previous;
	t_cmd		*tmp_cmd;
	char		*file;
	int			i;

	file = NULL;
	tmp_cmd = cmd_begin;
	if (tmp_cmd->redir)
		file = check_file(tmp_cmd->lredir, IN);
	i = 0;
	current = ft_init(1, file);
	while (++i < nb_cmd)
	{
		current->cmd = tmp_cmd;
		if (i != nb_cmd - 1)
		{
			if (tmp_cmd->next->redir)
				file = check_file(tmp_cmd->next->lredir, OUT);
			else 
				file = NULL;
			ft_pipe(current, i + 1, file);
		}
		//ft_exec_cmd(current, av, envp, ac);
		if (current->wr_out != 1)
			close(current->wr_out);
		if (current->rd_in != 0)
			close(current->rd_in);
		previous = current;
		current = current->next;
		ft_free_struc(previous);
	}
	while (wait(0) > 0)
	{
	}
}

/* need to change this function and t_pipe_cmd 
** to store whatever redirection is there for each cmd */
char	*check_file(t_redirIndex *redir_index, int file)
{
	t_redir	*tmp;
	int		i;

	tmp = redir_index->begin;
	i = -1;
	while (++i < redir_index->size)
	{
		if (tmp->type == file)
			return (tmp->file);
		tmp->next;
	}
	return (NULL);
}

t_pipe_cmd	*ft_init(int pos, char *file)
{
	t_pipe_cmd	*tmp;

	tmp = (t_pipe_cmd *)malloc(sizeof(t_pipe_cmd));
	tmp->rd_in = 0;
	tmp->file_name = file;
	tmp->pos = pos;
	tmp->wr_out = 1;
	return (tmp);
}

void	ft_pipe(t_pipe_cmd *current, int next_cmd, char *file)
{
	int	fd[2];

	current->next = ft_init(next_cmd, file);
	pipe(fd);
	current->wr_out = fd[1];
	current->next->rd_in = fd[0];
}

void	ft_exec_cmd(t_pipe_cmd *cur, char **av, char **env, int ac)
{
	pid_t	pid;
	char	*dir_cmd;
	char	**dir_cmd_flg;

	dir_cmd_flg = NULL;
	dir_cmd = NULL;
	ft_path(cur->cmd, &dir_cmd, env);
	dir_cmd_flg = ft_set_dir_cmd_flg(dir_cmd, cur->cmd);
	pid = fork();
	if (pid == 0)
		ft_multiple_child_ex(cur, av, dir_cmd_flg, ac);
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

void	ft_multiple_child_ex(t_pipe_cmd *cur, char **av, char **dir_cmd_flg, int ac)
{
	int	ret;

	ret = 0;
	if (cur->pos == 2) // case for the first cmd
		ret = ft_first(cur);
	if (cur->rd_in != 0 && cur->pos != ac - 2 && cur->pos != 2)
		dup2(cur->rd_in, 0);
	if (cur->wr_out != 1 && cur->pos != ac - 2 && cur->pos != 2)
	{
		close(cur->next->rd_in);
		dup2(cur->wr_out, 1);
		ret = 1;
	}
	else if (cur->pos == ac - 2) // case for the last cmd
		ret = ft_last(cur);
	if (ret == 1)
	{
		execve(dir_cmd_flg[0], dir_cmd_flg, NULL);
		//ft_error(dir_cmd_flg[0], av[cur->pos]);
		exit(ret);
	}
	exit(1);
}

int	ft_first(t_pipe_cmd *cur)
{
	int	fd;

	fd = open(cur->file_name, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("err: ", 2);
		ft_putstr_fd(cur->file_name, 2);
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

int	ft_last(t_pipe_cmd *cur)
{
	int	fd;

	fd = open(cur->file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("err: ", 2);
		ft_putstr_fd(cur->file_name, 2);
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


/*
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
*/
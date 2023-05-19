#include "../minishell.h"

//void ft_pipex(t_cmdIndex *index, char **path_dirs, t_envSom *envp_nodes)

void	ft_init_pipex(t_data *data)
{
	data->p_cmd.infile = -1;
	data->p_cmd.outfile = -1;
	data->p_cmd.prev_fd = -1;
	data->p_cmd.pipe_fd[0] = -1;
	data->p_cmd.pipe_fd[1] = -1;
	data->p_cmd.num_commands = -1;
	data->p_cmd.active_cmds = 0;
	data->p_cmd.heredoc_fd = -1;
}


int	close_if(int fd)
{
	if (fd > 2)
		close(fd);
	return (1);
}

void	ft_close_fds(t_data *data)
{
	if (data->p_cmd.prev_fd != -1)
		close_if(data->p_cmd.prev_fd);
	if (data->p_cmd.pipe_fd[0] != -1)
		close_if(data->p_cmd.pipe_fd[0]);
	if (data->p_cmd.pipe_fd[1] != -1)
		close_if(data->p_cmd.pipe_fd[1]);
}

void	ft_perror_clean_exit(t_data *data, char *str)
{
	perror(str);
	ft_close_fds(data);
	exit(-1);
}

void	ft_prepare_first(t_data *data)
{
	int	fd[2];

	fd[0] = -1;
	fd[1] = -1;
	if (pipe(fd) == -1)
		ft_perror_clean_exit(data, "Pipe failure");
	data->p_cmd.pipe_fd[0] = fd[0];
	data->p_cmd.pipe_fd[1] = fd[1];
	data->p_cmd.prev_fd = 0;
}

void	ft_prepare_next(t_data *data)
{
	int	fd[2];

	fd[0] = -1;
	fd[1] = -1;
	data->p_cmd.prev_fd = data->p_cmd.pipe_fd[0];
	close_if(data->p_cmd.pipe_fd[1]);
	if (pipe(fd) == -1)
		ft_perror_clean_exit(data, "Pipe failure");
	data->p_cmd.pipe_fd[0] = fd[0];
	data->p_cmd.pipe_fd[1] = fd[1];
}

void	ft_prepare_last(t_data *data)
{
	close_if(data->p_cmd.pipe_fd[1]);
	data->p_cmd.prev_fd = data->p_cmd.pipe_fd[0];
	data->p_cmd.pipe_fd[0] = -1;
	data->p_cmd.pipe_fd[1] = 1;
}

void	ft_prepare_pipes(t_cmd *cmd, t_data *data)
{
	printf("cmd @'%p' vs begin @'%p' vs end @'%p'\n", cmd, data->cmdIndex->begin, data->cmdIndex->end);
	if (cmd == data->cmdIndex->begin && data->cmdIndex->nb_cmd > 1)
	{
		printf("\tprepare_first\n");
		ft_prepare_first(data);
	}
	else if (cmd == data->cmdIndex->end)
	{
		printf("\tprepare_last\n");
		ft_prepare_last(data);
	}
	else
	{
		printf("\tprepare_next\n");
		ft_prepare_next(data);
	}
}	

int	ft_check_condition_to_execute(t_data *data)
{
	/* if there is only one cmd set the prev_fd to 0 or infile */
	if (data->cmdIndex->nb_cmd == 1)
	{
		if (data->cmdIndex->begin->redir)
		{
			if (data->p_cmd.infile > 0)
				data->p_cmd.pipe_fd[0] = data->p_cmd.infile;
			else
				data->p_cmd.pipe_fd[0] = IN;
			if (data->p_cmd.outfile > 0)
				data->p_cmd.pipe_fd[1] = data->p_cmd.outfile;
			else
				data->p_cmd.pipe_fd[1] = OUT;
		}
		else
		{
			data->p_cmd.pipe_fd[0] = IN;
			data->p_cmd.pipe_fd[1] = OUT;
		}
		data->p_cmd.prev_fd = data->p_cmd.pipe_fd[0];
	}
	if (data->p_cmd.prev_fd != -1)
		return (1);
	return (0);
}

void	ft_exec_command(t_cmd *cmd, t_data *data)
{
	int		pid;

	pid = fork();
	if (pid < -1)
		ft_perror_clean_exit(data, "Fork failure");
	if (pid == 0)
	{
		//printf("\texec_cmd. prev_fd:'%d'\n", data->p_cmd.prev_fd);
		if (dup2(data->p_cmd.prev_fd, IN) == -1)
			ft_perror_clean_exit(data, "Dup2 failure in child.");
		if (dup2(data->p_cmd.pipe_fd[1], OUT) == -1)
			ft_perror_clean_exit(data, "Dup2 failure in child.");
		ft_close_fds(data);
		if (cmd->is_built)
		{
			ft_builtins(cmd, data->env, data);
			exit(data->exit_return);
		}
		ft_execve(cmd, data);
	}
	else
		close_if(data->p_cmd.prev_fd);
}

void	ft_multiple_pipes(t_data *data)
{
	t_cmd		*cmd;

	cmd = data->cmdIndex->begin;
	//printf("cmd @ '%p', nb_cmd:'%d', cmd:'%s'\n", cmd, data->cmdIndex->nb_cmd, cmd->cmd);
	ft_init_pipex(data);
	while (cmd)
	{
		redir_fd(cmd, data);
		if (data->cmdIndex->nb_cmd > 1)
			ft_prepare_pipes(cmd, data);
		if (ft_check_condition_to_execute(data) == 1)
		{
			//printf("<<ft_exec_command>>\n");
			ft_exec_command(cmd, data);
			spec_built(cmd, data);
			data->p_cmd.active_cmds++;
		}
		cmd = cmd->next;
	}
	ft_wait_for_child_processes(data);
	ft_close_fds(data);
}

void	ft_wait_for_child_processes(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->p_cmd.active_cmds)
	{
		if (wait(&status) == -1)
			ft_perror_clean_exit(data, "Wait Failed");
		if (WIFSIGNALED(status) && WTERMSIG(status) != 13)
		{
			ft_putstr_fd("\nChild was terminated by signal ", 2);
			ft_putnbr_fd(WTERMSIG(status), 2);
			ft_putchar_fd('\n', 2);
		}
		i++;
	}
}


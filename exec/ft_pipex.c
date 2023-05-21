#include "../minishell.h"

//void ft_pipex(t_cmdIndex *index, char **path_dirs, t_envSom *envp_nodes)

//int	close_if(int fd)
//{
//	if (fd > 2)
//		close(fd);
//	return (1);
//}
//
///*
//void	ft_init_pipex(t_data *data)
//{
//	data->p_cmd.heredoc_fd = -1;
//	data->p_cmd.prev_fd = -1;
//	data->p_cmd.pipe_fd[0] = -1;
//	data->p_cmd.pipe_fd[1] = -1;
//}
//*/
//void	ft_close_fds(t_cmd *cmd)
//{
//	if (cmd->in_file != -1)
//		close_if(cmd->in_file);
//	if (cmd->out_file != -1)
//		close_if(cmd->out_file);
//	if (cmd->fd_in != -1)
//		close_if(cmd->fd_in);
//	if (cmd->fd_out != -1)
//		close_if(cmd->fd_out);
//}
//
//void	ft_close_all_fds(t_data *data)
//{
//	t_cmd	*cmd;
//
//	cmd = data->cmdIndex->begin;
//	while (cmd)
//	{
//		ft_close_fds(cmd);
//		cmd = cmd->next;
//	}
//}
//
//void	ft_perror_clean_exit(t_data *data, char *str)
//{
//	perror(str);
//	ft_close_all_fds(data);
//	exit(-1);
//}
//
////void	ft_set_redirection_fd(t_cmd *cmd, t_data *data, int pipe_in, int pipe_out)
//void	ft_set_redirection_fd(t_cmd *cmd)
//{
//	/* if there is infile available we replace STDIN of cmd by file_fd
//	** we also close PIPE_IN fd after fork() (it will be used in child to dup2 into STDIN of the next cmd) 
//	** not sure if necessary to close pipe_fd here of later after fork() !? */
//	if (cmd->redir && cmd->in_file != -1)
//	{
//		cmd->fd_in = cmd->in_file;
//	}
//	if (cmd->redir && cmd->out_file != -1)
//	{
//		cmd->fd_out = cmd->out_file;
//	}
//}
///*
//*/
//void	ft_prepare_first(t_cmd *cmd, t_data *data)
//{
//	int	fd[2];
//
//	fd[0] = -1;
//	fd[1] = -1;
//	if (pipe(fd) == -1)
//		ft_perror_clean_exit(data, "Pipe failure");
//	cmd->fd_in = STDIN_FILENO;
//	cmd->fd_out = fd[1];
//	cmd->next->fd_in = fd[0];
//	ft_set_redirection_fd(cmd);
//}
//
//void	ft_prepare_next(t_cmd *cmd, t_data *data)
//{
//	int	fd[2];
//
//	fd[0] = -1;
//	fd[1] = -1;
//	close_if(cmd->back->fd_out);
//	if (pipe(fd) == -1)
//		ft_perror_clean_exit(data, "Pipe failure");
//	cmd->fd_in = STDIN_FILENO;
//	cmd->fd_out = fd[1];
//	cmd->next->fd_in = fd[0];
//	ft_set_redirection_fd(cmd);
//}
//
//void	ft_prepare_last(t_cmd *cmd, t_data *data)
//{
//	(void)data;
//	/* fd_in shall hold previous pipe_in fd 
//	** we might change it if there is infile fd 
//	** might also change fd_out to out file if any */
//	close_if(cmd->back->fd_out);
//	cmd->fd_out = STDOUT_FILENO;
//	ft_set_redirection_fd(cmd);
//}
//
//void	ft_prepare_pipes(t_cmd *cmd, t_data *data)
//{
//	//printf("cmd @'%p' vs begin @'%p' vs end @'%p'\n", cmd, data->cmdIndex->begin, data->cmdIndex->end);
//	if (cmd == data->cmdIndex->begin)
//	{
//		if (data->cmdIndex->nb_cmd == 1)
//		{
//			printf("\tprepare_first (one cmd only)\n");
//			cmd->fd_in = STDIN_FILENO;
//			cmd->fd_out = STDOUT_FILENO;
//			ft_set_redirection_fd(cmd);
//		}
//		else
//		{
//			printf("\tprepare_first (piping)\n");
//			ft_prepare_first(cmd, data);
//		}
//	}
//	else if (cmd == data->cmdIndex->end)
//	{
//		printf("\tprepare_last\n");
//		ft_prepare_last(cmd, data);
//	}
//	else
//	{
//		printf("\tprepare_next\n");
//		ft_prepare_next(cmd, data);
//	}
//}	
//
///*
//int	ft_check_condition_to_execute(t_data *data)
//{
//	if (data->p_cmd.prev_fd != -1)
//		return (1);
//	return (0);
//}
//*/
//
//void	ft_exec_command(t_cmd *cmd, t_data *data)
//{
//	int		pid;
//
//	pid = fork();
//	if (pid < -1)
//		ft_perror_clean_exit(data, "Fork failure");
//	if (pid == 0)
//	{
//		printf("\texec_cmd. fd_in:'%d', fd_out:'%d', in_file:'%d', out_file:'%d'\n", cmd->fd_in, cmd->fd_out, cmd->in_file, cmd->out_file);
//		if (dup2(cmd->fd_in, IN) == -1)
//			ft_perror_clean_exit(data, "(fd_in) Dup2 failure in child.");
//		if (dup2(cmd->fd_out, OUT) == -1)
//			ft_perror_clean_exit(data, "(fd_out) Dup2 failure in child.");
//		ft_close_fds(cmd);
//		//close_if(cmd->fd_out);
//		/*
//		if (dup2(data->p_cmd.prev_fd, IN) == -1)
//			ft_perror_clean_exit(data, "(prev_fd) Dup2 failure in child.");
//		if (dup2(data->p_cmd.pipe_fd[1], OUT) == -1)
//			ft_perror_clean_exit(data, "(pipe_fd[1]) Dup2 failure in child.");
//		ft_close_fds(data);
//		*/
//		if (cmd->is_built)
//		{
//			ft_builtins(cmd, data->env, data);
//			exit(data->exit_return);
//		}
//		ft_execve(cmd, data);
//	}
//	else
//	{
//		close_if(cmd->fd_in);
//		//close_if(cmd->fd_out);
//		//dup2(cmd->fd_in, IN);
//	}
//}
//
//void	ft_multiple_pipes(t_data *data)
//{
//	t_cmd		*cmd;
//
//	cmd = data->cmdIndex->begin;
//	//printf("cmd @ '%p', nb_cmd:'%d', cmd:'%s'\n", cmd, data->cmdIndex->nb_cmd, cmd->cmd);
//	//ft_init_pipex(data);
//	while (cmd)
//	{
//
//		ft_prepare_pipes(cmd, data);
//	
//		printf("\tinfile:'%d', outfile:'%d'\tfd_in:'%d', fd_out:'%d'\n", cmd->in_file, cmd->out_file, cmd->fd_in, cmd->fd_out);
//		spec_built(cmd, data);
//		ft_exec_command(cmd, data);
//		/*
//		if (ft_check_condiion_to_execute(data) == 1)
//		{
//			//printf("<<ft_exec_command>>\n");
//			ft_exec_command(cmd, data);
//			//data->p_cmd.active_cmds++;
//		}
//		*/
//		cmd = cmd->next;
//	}
//	ft_wait_for_child_processes(data);
//	ft_close_all_fds(data);
//}
//
//void	ft_wait_for_child_processes(t_data *data)
//{
//	int	i;
//	int	status;
//
//	i = 0;
//	//while (i < data->p_cmd.active_cmds)
//	while (i < data->cmdIndex->nb_cmd)
//	{
//		if (wait(&status) == -1)
//			ft_perror_clean_exit(data, "Wait Failed");
//		if (WIFSIGNALED(status) && WTERMSIG(status) != 13)
//		{
//			ft_putstr_fd("\nChild was terminated by signal ", 2);
//			ft_putnbr_fd(WTERMSIG(status), 2);
//			ft_putchar_fd('\n', 2);
//		}
//		i++;
//	}
//}
//
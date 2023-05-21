#include "../minishell.h"

void	redirect_in_out(t_cmd *cmd, int *fd)
{
	close(fd[0]);
	if (cmd->in_file >= 0)
	{
		dup2(cmd->in_file, 0);
		close(cmd->in_file);
	}
	if (cmd->out_file >= 0)
	{
		dup2(cmd->out_file, 1);
		close(cmd->out_file);
	}
	else if (cmd->next != NULL)
		dup2(fd[1], 1);
	close(fd[1]);
}

void	child_process(t_data *data, t_cmd *cmd, int *fd)
{
	//if (cmd->skip_cmd)
	//	data->exit_code = 1;
	//else if (is_built_in(cmd->cmd_param[0]))
	//{
	//	close(fd[0]);
	//	if (cmd->outfile < 0 && cmd->next)
	//		cmd->outfile = fd[1];
	//	else
	//		close(fd[1]);
	//	launch_built_in(data, cmd);
	//}
	//if (command_exist(data, cmd))
	//{
	redirect_in_out(cmd, fd);
	ft_execve(cmd, data);
	exit_process(data, fd);
		//print_error_command(cmd->cmd_param[0], 1);
		//data->exit_code = 126;
	//}
	//else
	//{
	//	print_error_command(cmd->cmd_param[0], 2);
	//	data->exit_code = 127;
	//}
}

void	ft_launch_cmd(t_data *data, t_cmd *cmd, int *fd)
{
	global.pid = fork();
	if (global.pid < 0)
		return ;
	else if (global.pid == 0)
	{
		if (cmd->argv[0])
			child_process(data, cmd, fd);
		//else
		//{
		//	data->exit_code = 0;
		//	exit_process(data, fd);
		//}
	}
	else
		parent_process(cmd, fd);
}

int	ft_ft_exec(t_data *data)
{
	t_cmd	*cmd;
	int		fd[2];

	cmd = data->cmdIndex->begin;
	//if (cmds && cmds->skip_cmd == false && !cmds->next 
	//&& (cmds->cmd_param[0] && is_built_in(cmds->cmd_param[0])))
	//	launch_built_in(data, cmds);
	while (cmd)
	{
		if (pipe(fd) == -1)
			return (-1);
		ft_launch_cmd(data, cmd, fd);
		cmd = cmd->next;
	}
	wait_all_and_finish(data, data->cmdIndex->begin);
	return (1);
}

void	parent_process(t_cmd *cmd, int *fd)
{
	close(fd[1]);
	if (cmd->in_file >= 0)
		close(cmd->in_file);
	if (cmd->in_file == -2)
		cmd->in_file = fd[0];
	if (cmd->next && cmd->next->in_file == -2)
		cmd->next->in_file = fd[0];
	else
		close(fd[0]);
	return ;
}

void	exit_process(t_data *data, int *fd)
{
	t_cmd	*current;

	current = data->cmdIndex->begin;
	while (current)
	{
		if (current->in_file >= 0)
			close(current->in_file);
		if (current->out_file >= 0)
			close(current->out_file);
		current = current->next;
	}
	close(fd[0]);
	close(fd[1]);
	//free_cmd(&data->cmd);
	//free_token_lst(data);
	//free_tab_str(&data->test, -1);
	//free_env(data->env);
	exit(data->exit_return);
}

void	wait_all_and_finish(t_data *data, t_cmd *cmds)
{
	int	status;
	int	pid;

	while (cmds)
	{
		pid = waitpid(0, &status, 0);
		if (pid == global.pid)
		{
			if (WIFEXITED(status))
				data->exit_return = WEXITSTATUS(status);
		}
		if (cmds->out_file >= 0)
			close(cmds->out_file);
		if (cmds->in_file >= 0)
			close(cmds->in_file);
		cmds = cmds->next;
	}
}
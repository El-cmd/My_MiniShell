/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:26:30 by vloth             #+#    #+#             */
/*   Updated: 2023/09/08 18:42:51 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int	n;

	redirect_in_out(cmd, fd);
	if (cmd->is_built && !cmd->spec_built)
	{
		ft_builtins(cmd, data->env, data);
		n = data->exit_return;
		free_everything(data);
		exit(n);
	}
	ft_execve(cmd, data);
	exit_process(data, fd);
}

void	ft_launch_cmd(t_data *data, t_cmd *cmd, int *fd)
{
	cmdbloc_signal();
	g_pid = fork();
	if (g_pid < 0)
	{
		perror("fork");
		return ;
	}
	else if (g_pid == 0)
	{
		if (cmd->argv && cmd->argv[0])
			child_process(data, cmd, fd);
		_exit(EXIT_FAILURE);
	}
	else
		parent_process(cmd, fd);
}

int	ft_ft_exec(t_data *data)
{
	t_cmd	*cmd;
	int		fd[2];

	cmd = data->cmd_index->begin;
	while (cmd)
	{
		if (cmd->out_file == -1 || cmd->in_file == -1)
			ft_putstr_fd("Error: redirection\n", 2);
		else if (cmd->spec_built)
			spec_built(cmd, data);
		else
		{
			if (pipe(fd) == -1)
				return (-1);
			else
				ft_launch_cmd(data, cmd, fd);
		}
		cmd = cmd->next;
	}
	wait_all_and_finish(data->cmd_index->begin, data);
	free_list_second(data);
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

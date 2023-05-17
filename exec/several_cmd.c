/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   several_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:26:00 by vloth             #+#    #+#             */
/*   Updated: 2023/05/15 22:30:06 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// execution d'un seul pipe et donc deux commandes
void wait_all(t_data *data)
{
	int status;
	int pid;
	t_cmd *cmd;
	cmd = data->cmdIndex->begin;
	while (cmd)
	{
		pid = waitpid(0, &status, 0);
		if (pid == global.pid)
		{
			if (WIFEXITED(status))
				data->exit_return = WEXITSTATUS(status);
		}
		cmd = cmd->next;
	}
}

void	launch_cmd(t_cmd *cmd, t_data *data, int *fd)
{
	global.pid = fork();
	if (global.pid < 0)
		return ;
	else if (global.pid == 0)
		ft_child(cmd, data->env, fd, data);
	else
		ft_parent(fd);
	return ;
}

void	ft_exec(t_data *data)
{
	t_cmd *cmd;
	int	fd[2];

	cmd = data->cmdIndex->begin;
	if (data->cmdIndex->nb_cmd == 1 && ft_builtins(cmd, data->env, data) == 0)
		return ;
	while (cmd)
	{
		if (pipe(fd) == -1)
			return ;
		launch_cmd(cmd, data, fd);
		cmd = cmd->next;
	}
	wait_all(data);
}

void	ft_child(t_cmd *cmd, t_envSom *env, int fd[2], t_data *d)
{
	if (cmd->next != NULL)
		dup2(fd[1], OUT);
	if (cmd->next == NULL)
		dup2(fd[0], IN);
	close(fd[0]);
	close(fd[1]);
	if (ft_builtins(cmd, env, d) == 0)
		exit(d->exit_return);
	ft_execve(cmd, d);
}

void	ft_parent(int *fd)
{
	close(fd[1]);
	close(fd[0]);		
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:14:50 by nspeciel          #+#    #+#             */
/*   Updated: 2023/09/03 15:18:55 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_process(t_data *data, int *fd)
{
	t_cmd	*current;

	current = data->cmd_index->begin;
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
	free_everything(data);
	exit(data->exit_return);
}

void	wait_all_and_finish(t_cmd *cmds, t_data *data)
{
	int	status;
	int	pid;

	while (cmds)
	{
		pid = waitpid(0, &status, 0);
		if (pid == g_global.pid)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:26:49 by vloth             #+#    #+#             */
/*   Updated: 2023/07/10 15:26:02 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// fonction d'execution
void	ft_execve(t_cmd *cmd, t_data *data)
{
	int		y;
	char	*exec;
	int		i;

	y = 0;
	i = 0;
	while (data->path_exec[++y])
	{
		if (i == 0)
		{
			data->exit_return = execve(cmd->argv[0], cmd->argv, data->envp);
			i++;
		}
		exec = ft_strjoin(ft_strjoin(data->path_exec[y], "/"), cmd->argv[0]);
		data->exit_return = execve(exec, cmd->argv, data->envp);
		free(exec);
	}
	ft_putstr_fd(cmd->argv[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	data->exit_return = 127;
	exit(data->exit_return);
}

void	exec(t_data *data)
{
	t_cmdIndex	*index;

	index = data->cmdIndex;
	spec_built_first(data);
	if (index->nb_cmd)
		ft_ft_exec(data);
}

void	spec_built(t_cmd *cmd, t_data *data)
{
	if (cmd->spec_built == 1)
		ft_exit(cmd, data);
	else if (cmd->spec_built == 2)
		ft_cd(cmd, data->env, data);
	else
		return ;
}

void	spec_built_first(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmdIndex->begin;
	while (cmd)
	{
		if (ft_strcmp(cmd->argv[0], "cd") == 0)
			cmd->spec_built = 2;
		else if (ft_strcmp(cmd->argv[0], "exit") == 0)
			cmd->spec_built = 1;
		else
			cmd->spec_built = 0;
		cmd = cmd->next;
	}
}

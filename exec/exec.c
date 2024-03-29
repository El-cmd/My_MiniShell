/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspeciel <nspeciel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:26:49 by vloth             #+#    #+#             */
/*   Updated: 2023/09/06 16:12:16 by nspeciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// fonction d'execution
void	ft_execve(t_cmd *cmd, t_data *data)
{
	int		y;
	char	*exec;
	char	*tmp;
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
		tmp = ft_strjoin(data->path_exec[y], "/");
		exec = ft_strjoin(tmp, cmd->argv[0]);
		free(tmp);
		data->exit_return = execve(exec, cmd->argv, data->envp);
		free(exec);
	}
	ft_putstr_fd(cmd->argv[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	free_everything(data);
	i = 127;
	exit(i);
}

void	exec(t_data *data)
{
	t_cmd_index	*index;

	index = data->cmd_index;
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
	else if (cmd->spec_built == 3)
		ft_export(data->env, cmd, data);
	else if (cmd->spec_built == 4)
		ft_unset(data->env, cmd, data);
	else
		return ;
}

void	spec_built_first(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmd_index->begin;
	while (cmd)
	{
		if (cmd != NULL && cmd->argv != NULL && cmd->argv[0] != NULL)
		{
			if (ft_strcmp(cmd->argv[0], "cd") == 0)
				cmd->spec_built = 2;
			else if (ft_strcmp(cmd->argv[0], "exit") == 0)
				cmd->spec_built = 1;
			else if (ft_strcmp(cmd->argv[0], "export") == 0)
				cmd->spec_built = 3;
			else if (ft_strcmp(cmd->argv[0], "unset") == 0)
				cmd->spec_built = 4;
			else
				cmd->spec_built = 0;
		}
		else
		{	
			cmd->spec_built = -1;
		}
		cmd = cmd->next;
	}
}

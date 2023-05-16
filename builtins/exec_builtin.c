/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:26:18 by vloth             #+#    #+#             */
/*   Updated: 2023/05/16 15:05:30 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//ne pas oublier que si il des redirection la commande est dans cmd->just_cmd
//fonction qui execute les builtins un peu caca bouda

void is_built_redir(t_cmd *cmd)
{
	if ((ft_strncmp(cmd->just_cmd, "env", 3) == 0 \
		 && ft_strlen(cmd->just_cmd) == 3) \
		 || (ft_strncmp(cmd->just_cmd, "pwd", 3) == 0 \
		 && ft_strlen(cmd->just_cmd) == 3) \
		 || (ft_strncmp(cmd->just_cmd, "cd", 2) == 0) \
		 || (ft_strncmp(cmd->just_cmd, "echo", 4) == 0) \
		 || (ft_strncmp(cmd->just_cmd, "exit", 4) == 0) \
		 || (ft_strncmp(cmd->just_cmd, "export", 6) == 0) \
		 || (ft_strncmp(cmd->just_cmd, "unset", 5) == 0))
		cmd->is_built = true;
	else
		cmd->is_built = false;
}

void	is_built_no_redir(t_cmd *cmd)
{
	if ((ft_strncmp(cmd->cmd, "env", 3) == 0 && ft_strlen(cmd->cmd) == 3) \
		 || (ft_strncmp(cmd->cmd, "pwd", 3) == 0 && ft_strlen(cmd->cmd) == 3) \
		 || (ft_strncmp(cmd->cmd, "cd", 2) == 0) \
		 || (ft_strncmp(cmd->cmd, "echo", 4) == 0) \
		 || (ft_strncmp(cmd->cmd, "exit", 4) == 0) \
		 || (ft_strncmp(cmd->cmd, "export", 6) == 0) \
		 || (ft_strncmp(cmd->cmd, "unset", 5) == 0))
		cmd->is_built = true;
	else
		cmd->is_built = false;	
}

void is_built(t_data *data)
{
	t_cmd *cmd;
	
	cmd = data->cmdIndex->begin;
	while (cmd)
	{
		if (cmd->redir)
			is_built_redir(cmd);
		else
			is_built_no_redir(cmd);
		cmd = cmd->next;
	}	
}

int	ft_builtins(t_cmd *cmd, t_envSom *env, t_data *data)
{
	if (ft_strncmp(cmd->cmd, "env", 3) == 0 && ft_strlen(cmd->cmd) == 3)
	{
		ft_env(env, data);
		return 0;
	}
	else if (ft_strncmp(cmd->cmd, "pwd", 3) == 0 && ft_strlen(cmd->cmd) == 3)
	{
		ft_pwd(data);
		return 0;
	}
	else if (ft_strncmp(cmd->cmd, "cd", 2) == 0)
	{
		ft_cd(cmd, env, data);
		return 0;
	}
	else if (ft_strncmp(cmd->cmd, "echo", 4) == 0)
	{
		ft_echo(cmd, data);
		return 0;
	}
	else if (ft_strncmp(cmd->cmd, "exit", 4) == 0)
		ft_exit(cmd, data);
	else if (ft_strncmp(cmd->cmd, "export", 6) == 0)
	{
		ft_export(env, cmd, data);
		return 0;
	}
	else if (ft_strncmp(cmd->cmd, "unset", 5) == 0)
	{
		ft_unset(env, cmd, data);
		return 0;
	}
	return 1;
}
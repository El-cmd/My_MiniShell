/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:26:18 by vloth             #+#    #+#             */
/*   Updated: 2023/05/13 18:26:19 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


//fonction qui execute les builtins un peu caca bouda
int	ft_builtins(t_cmd *cmd, t_envSom *env)
{
	if (ft_strncmp(cmd->cmd, "env", 3) == 0 && ft_strlen(cmd->cmd) == 3)
	{
		ft_env(env);
		return 0;
	}
	else if (ft_strncmp(cmd->cmd, "pwd", 3) == 0 && ft_strlen(cmd->cmd) == 3)
	{
		ft_pwd();
		return 0;
	}
	else if (ft_strncmp(cmd->cmd, "cd", 2) == 0)
	{
		ft_cd(cmd, env);
		return 0;
	}
	else if (ft_strncmp(cmd->cmd, "echo", 4) == 0)
	{
		ft_echo(cmd);
		return 0;
	}
	else if (ft_strncmp(cmd->cmd, "exit", 4) == 0 && ft_strlen(cmd->cmd) == 4)
		ft_exit();
	else if (ft_strncmp(cmd->cmd, "export", 6) == 0)
	{
		ft_export(env, cmd);
		return 0;
	}
	else if (ft_strncmp(cmd->cmd, "unset", 5) == 0)
	{
		ft_unset(env, cmd);
		return 0;
	}
	return 1;
}
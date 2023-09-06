/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldoctor <eldoctor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:26:18 by vloth             #+#    #+#             */
/*   Updated: 2023/09/06 16:29:09 by eldoctor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//ne pas oublier que si il a des redirection la commande est dans cmd->just_cmd
//fonction qui execute les builtins un peu caca bouda
void	is_built_redir(t_cmd *cmd)
{
	if (cmd != NULL && cmd->argv != NULL && cmd->argv[0] != NULL)
	{
		if (!ft_strcmp(cmd->argv[0], "env")
			|| !ft_strcmp(cmd->argv[0], "pwd")
			|| !ft_strcmp(cmd->argv[0], "cd")
			|| !ft_strcmp(cmd->argv[0], "echo")
			|| !ft_strcmp(cmd->argv[0], "\"echo\"")
			|| !ft_strcmp(cmd->argv[0], "exit")
			|| !ft_strcmp(cmd->argv[0], "export")
			|| !ft_strcmp(cmd->argv[0], "unset"))
		{
			cmd->is_built = true;
		}
		else
		{
			cmd->is_built = false;
		}
	}
	else
	{
		cmd->is_built = false;
	}
}

void	is_built(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmd_index->begin;
	while (cmd)
	{
		is_built_redir(cmd);
		cmd = cmd->next;
	}
}

int	ft_builtins(t_cmd *cmd, t_env_som *env, t_data *data)
{
	if (cmd != NULL && cmd->argv != NULL && cmd->argv[0] != NULL)
	{
		if (!ft_strcmp(cmd->argv[0], "env") && !cmd->argv[1])
		{
			ft_env(env, data);
			return (0);
		}
		else if (!ft_strcmp(cmd->argv[0], "pwd"))
		{
			ft_pwd(cmd, data);
			return (0);
		}
		else if (!ft_strcmp(cmd->argv[0], "echo") || !ft_strcmp(cmd->argv[0], "\"echo\""))
		{
			ft_echo(cmd, data);
			return (0);
		}
	}
	return (1);
}

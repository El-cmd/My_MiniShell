/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:26:49 by vloth             #+#    #+#             */
/*   Updated: 2023/05/17 19:20:30 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
void exec(t_cmdIndex *cmd, char **envp, t_envSom *envp_nodes);
void ft_execve(char *cmd, char **envp);
*/
// fonction d'execution
void ft_execve(t_cmd *cmd, t_data *data)
{
	int y;
	char *exec;

	no_str(cmd->cmd);
	y = 0;
	while (data->path_exec[++y])
	{
		exec = ft_strjoin(ft_strjoin(data->path_exec[y], "/"), cmd->argv[0]);
		data->exit_return = execve(exec, cmd->argv, data->envp);
		free(exec);
	}
	ft_putstr_fd(cmd->argv[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	data->exit_return = errno;
	exit(data->exit_return);
}

//regarde quel execution faire si une ou plusieur cmd
//void exec(t_cmdIndex *cmd, char **envp, t_envSom *envp_nodes)
void exec(t_data *data)
{
	t_cmdIndex *index;

	index = data->cmdIndex;
	//if (index->begin->redir == true)
	//	return ;
	if (index->nb_cmd == 1)
		ft_exec(data);
	else if (index->nb_cmd > 1)
	 	ft_multiple_pipes(data);
	  	//ft_pipe_exec(data);
}
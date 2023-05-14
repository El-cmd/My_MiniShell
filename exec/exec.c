/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:26:49 by vloth             #+#    #+#             */
/*   Updated: 2023/05/13 18:26:50 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
void exec(t_cmdIndex *cmd, char **envp, t_envSom *envp_nodes);
void ft_execve(char *cmd, char **envp);
*/
// fonction d'execution
void ft_execve(char *cmd, char **envp, t_data *data)
{
	char **cmdarg;
	int y;
	char *exec;

	no_str(cmd);
	y = 0;
	cmdarg = ft_split(cmd, ' ');
	while (envp[++y])
	{
		exec = ft_strjoin(ft_strjoin(envp[y], "/"), cmdarg[0]);
		data->exit_return = execve(exec, cmdarg, envp);
		free(exec);
	}
	ft_putstr_fd(cmdarg[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	free_tab(cmdarg);
	data->exit_return = errno;
	exit(data->exit_return);
}

//regarde quel execution faire si une ou plusieur cmd
//void exec(t_cmdIndex *cmd, char **envp, t_envSom *envp_nodes)
void exec(t_data *data)
{
	t_cmdIndex *index;
	char **path_dirs;
	t_envSom *envp_nodes;
	t_cmd *cmd;

	index = data->cmdIndex;
	path_dirs = data->path_exec;
	envp_nodes = data->env;
	cmd = index->begin;
	if (index->begin->redir == true)
		return ;
	if (index->nb_cmd == 1)
		simple_cmd(envp_nodes, cmd, path_dirs, index, data);
	else if (index->nb_cmd == 2)
		ft_simple_pipe(index, path_dirs, envp_nodes, data);
	else if (index->nb_cmd > 2)
	 	ft_pipex(data);
	 	//ft_pipex(index, path_dirs, envp_nodes);
		//multi_pipe(index, path_dirs, envp_nodes);
}
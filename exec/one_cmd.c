/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:25:55 by vloth             #+#    #+#             */
/*   Updated: 2023/05/13 18:25:56 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//execution dune seule cmd sans redirection ou pipe
int	simple_cmd(t_envSom *env, t_cmd *cmd, char **envp, t_cmdIndex *cmdIndex)
{
	pid_t pid;

	if (cmdIndex->nb_cmd == 1)
	{
		if (ft_builtins(cmd, env) == 0)
			return (0);
		pid = fork();
		if (pid == 0)
			ft_execve(cmd->cmd, envp);
		else
			wait(NULL);
	}
	return 0;
}

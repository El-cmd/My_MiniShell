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
int	simple_cmd(t_envSom *env, t_cmd *cmd, char **e, t_cmdIndex *c, t_data *d)
{
	pid_t pid;

	if (c->nb_cmd == 1)
	{
		if (ft_builtins(cmd, env, d) == 0)
			return (0);
		pid = fork();
		if (pid == 0)
			ft_execve(cmd->cmd, e, d);
		else
			wait(NULL);
	}
	return 0;
}

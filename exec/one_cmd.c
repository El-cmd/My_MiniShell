/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:25:55 by vloth             #+#    #+#             */
/*   Updated: 2023/05/15 22:24:14 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//execution dune seule cmd sans redirection ou pipe
int	simple_cmd(t_envSom *env, t_cmd *cmd, t_cmdIndex *c, t_data *d)
{
	if (c->nb_cmd == 1)
	{
		if (ft_builtins(cmd, env, d) == 0)
			return (0);
		global.pid = fork();
		if (global.pid == 0)
			ft_execve(cmd, d);
		else
			wait(NULL);
	}
	return 0;
}

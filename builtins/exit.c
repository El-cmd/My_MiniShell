/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:26:22 by vloth             #+#    #+#             */
/*   Updated: 2023/07/10 14:37:52 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// Gestion de l'exit
void	ft_exit(t_cmd *cmd, t_data *data)
{
	int	n;

	if (cmd->redir == false)
	{
		if (ft_strlen(cmd->cmd) > 4)
			data->exit_return = ft_atoi_exit(cmd->cmd + 4);
		else
			data->exit_return = 0;
	}
	else
	{
		if (ft_strlen(cmd->just_cmd) > 4)
			data->exit_return = ft_atoi_exit(cmd->just_cmd + 4);
		else
			data->exit_return = 0;
	}
	ft_putstr_fd("exit\n", 1);
	cmd->spec_built = 1;
	n = data->exit_return;
	free_everything(data);
	exit(n);
}

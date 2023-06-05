/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:26:14 by vloth             #+#    #+#             */
/*   Updated: 2023/05/21 23:38:42 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//echo sans le \n mais encore quelque bug
int ft_echo_n(t_cmd *cmd)
{
	if (cmd->argv[2])
		ft_putstr_fd(cmd->argv[2], 1);
	return 0;
}

//execute echo mais encore quelques truc a regler
int	ft_echo(t_cmd *cmd, t_data *data)
{
	int i;

	i = 0;
	if (cmd->argv[1] && !ft_strcmp(cmd->argv[0], "echo") && !ft_strcmp(cmd->argv[1], "-n"))
	{
		ft_echo_n(cmd);
		data->exit_return = 0;
	}
	else
	{
		while (cmd->argv[++i])
		{
			ft_putstr_fd(cmd->argv[i], 1);
			write(1, " ", 1);
		}
		ft_putstr_fd("\n", 1);
		data->exit_return = 0;
	}
	return 0;	
}
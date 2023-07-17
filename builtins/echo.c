/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:26:14 by vloth             #+#    #+#             */
/*   Updated: 2023/07/10 14:54:11 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//echo sans le \n mais encore quelque bug
int	ft_echo_n(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	int y = 0;
	while (cmd->argv[i])
	{
		if (cmd->argv[i][0] == '-' && cmd->argv[i][1] == 'n')
		{
			if (j == 0 || j == 1)
				j = 2;
			while (cmd->argv[i] && cmd->argv[i][j] == 'n')
				j++;
		}
		if (cmd->argv[i][j] != '\0')
			j = 0;
		while (cmd->argv[i][j])
		{
			y = 1;
			if (cmd->argv[i][j] == '"' || cmd->argv[i][j] == '\'')
				j++;
			else
				ft_putchar_fd(cmd->argv[i][j], 1);
			j++;
		}
		if (y && cmd->argv[i + 1])
			write(1, " ", 1);
		i++;
		j = 0;
	}
	return (0);
}

//execute echo mais encore quelques truc a regler
int	ft_echo(t_cmd *cmd, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (cmd->argv[1] && !ft_strcmp(cmd->argv[0], "echo") \
	&& !ft_strncmp(cmd->argv[1], "-n", 2))
	{
		ft_echo_n(cmd);
		data->exit_return = 0;
	}
	else
	{
		while (cmd->argv[++i])
		{
			while (cmd->argv[i][j])
			{
				if (cmd->argv[i][j] == '"' || cmd->argv[i][j] == '\'')
					j++;
				else
					ft_putchar_fd(cmd->argv[i][j], 1);
				j++;
			}
			if (cmd->argv[i + 1])
				write(1, " ", 1);
			j = 0;
		}
		ft_putstr_fd("\n", 1);
		data->exit_return = 0;
	}
	return (0);
}

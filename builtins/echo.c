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
int ft_echo_n(char *str, t_cmd *cmd)
{
	if (cmd->redir)
		str = cmd->just_cmd + 8;
	else
		str = cmd->cmd + 8;
	str = ft_strtrim(str, " ");
	ft_putstr_fd(str, 1);
	return 0;
}

void echo_redir(t_cmd *cmd, t_data *data, char *str)
{
	if (ft_strncmp(cmd->just_cmd, "echo -n ", 8)== 0)
	{
		ft_echo_n(str, cmd);
		data->exit_return = 0;
	}
	else
	{
		str = cmd->just_cmd + 5;
		str = ft_strtrim(str, " ");
		ft_putendl_fd(str, 1);
		data->exit_return = 0;
	}
}

//execute echo mais encore quelques truc a regler
int	ft_echo(t_cmd *cmd, t_data *data)
{
	char *str;

	str = NULL;
	if (cmd->redir)
		echo_redir(cmd, data, str);
	else
	{
		if (ft_strncmp(cmd->cmd, "echo -n ", 8)== 0)
		{
			ft_echo_n(str, cmd);
			data->exit_return = 0;
		}
		else
		{
			str = cmd->cmd + 5;
			str = ft_strtrim(str, " ");
			ft_putendl_fd(str, 1);
			data->exit_return = 0;
		}
	}
	return 0;
}
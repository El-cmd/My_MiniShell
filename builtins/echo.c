/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspeciel <nspeciel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:26:14 by vloth             #+#    #+#             */
/*   Updated: 2023/09/04 03:00:39 by nspeciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//echo sans le \n
void	ft_echo_n(t_cmd *cmd, int i)
{
	int	j;

	j = 0;
	while (cmd->argv[i])
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
		i++;
	}
}

//execute echo mais encore quelques truc a regler
void	ft_echo_text(char *text)
{
	int	i;

	i = 0;
	while (text[i])
	{
		if (text[i] != '"' && text[i] != '\'')
			ft_putchar_fd(text[i], 1);
		i++;
	}
}

int	just_n(char *str)
{
	int	i;

	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	pass_n(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->argv[i] && !ft_strncmp(cmd->argv[i], "-n", 2))
	{
		if (just_n(cmd->argv[i]))
			return (i);
		i++;
	}
	return (i);
}

void	ft_echo(t_cmd *cmd, t_data *data)
{
	int	i;

	i = 1;
	if (cmd->argv[i] && !ft_strcmp(cmd->argv[0], "echo"))
	{
		if (echo_quote(cmd))
			return ;
		if (!ft_strncmp(cmd->argv[i], "-n", 2))
		{	
			ft_echo_n(cmd, pass_n(cmd));
			data->exit_return = 0;
			return ;
		}
		while (cmd->argv[i])
		{
			ft_echo_text(cmd->argv[i]);
			if (cmd->argv[i + 1])
				write(1, " ", 1);
			i++;
		}
	}
	ft_putstr_fd("\n", 1);
	data->exit_return = 0;
}

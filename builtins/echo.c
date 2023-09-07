/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:26:14 by vloth             #+#    #+#             */
/*   Updated: 2023/09/07 22:49:22 by vloth            ###   ########.fr       */
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

//execute echo
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
	int		i;
	int		j;
	bool	sup_newline;
	bool	valid_opt;

	i = 1;
	sup_newline = false;
	if (cmd->argv[i] && (!ft_strcmp(cmd->argv[0], "echo")))
	{
		while (cmd->argv[i])
		{
			if (!ft_strncmp(cmd->argv[i], "-n", 2))
			{
				j = 2;
				valid_opt = true;
				while (cmd->argv[i][j])
				{
					if (cmd->argv[i][j] != 'n')
					{
						valid_opt = false;
						break ;
					}
					j++;
				}
				if (valid_opt)
				{
					sup_newline = true;
					i++;
					continue ;
				}
			}
			ft_echo_text(cmd->argv[i]);
			if (cmd->argv[i + 1])
				write(1, " ", 1);
			i++;
		}
	}
	if (!sup_newline)
		ft_putchar_fd('\n', 1);
	data->exit_return = 0;
}

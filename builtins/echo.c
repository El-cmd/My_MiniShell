/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspeciel <nspeciel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:26:14 by vloth             #+#    #+#             */
/*   Updated: 2023/09/08 16:49:17 by nspeciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//echo sans le \n
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

bool	is_valid_option(char *option)
{
	int	j;

	if (option[0] == '-' && option[1] == 'n')
	{
		j = 2;
		while (option[j])
		{
			if (option[j] != 'n')
				return (false);
			j++;
		}
		return (true);
	}
	return (false);
}

void	ft_echo(t_cmd *cmd, t_data *data)
{
	int		i;
	bool	suppress_newline;

	i = 1;
	suppress_newline = false;
	if (cmd->argv[i] && strcmp(cmd->argv[0], "echo") == 0)
	{
		while (cmd->argv[i])
		{
			if (is_valid_option(cmd->argv[i]))
			{
				suppress_newline = true;
				i++;
				continue ;
			}
			ft_echo_text(cmd->argv[i]);
			if (cmd->argv[i + 1])
				write(1, " ", 1);
			i++;
		}
	}
	if (!suppress_newline)
		write(1, "\n", 1);
	data->exit_return = 0;
}

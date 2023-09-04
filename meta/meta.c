/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspeciel <nspeciel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:29:24 by vloth             #+#    #+#             */
/*   Updated: 2023/09/03 16:40:44 by nspeciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	only_dollar(char *str, int i)
{
	i = i + 1;
	if (str[i] == ' ' || str[i] == '\0')
		return (1);
	else
		return (0);
}

void	is_meta(t_data *data)
{
	int		i;
	t_cmd	*cmd;
	int		m;

	i = 0;
	m = 0;
	cmd = data->cmd_index->begin;
	while (cmd)
	{
		while (cmd->cmd[i])
		{
			if (cmd->cmd[i] == '$' && only_dollar(cmd->cmd, i) == 0)
			{
				cmd->have_meta = true;
				m = 1;
			}
			i++;
		}
		if (m == 0)
			cmd->have_meta = false;
		i = 0;
		cmd = cmd->next;
	}
}

int	is_meta_second(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && only_dollar(str, i) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	is_simple_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

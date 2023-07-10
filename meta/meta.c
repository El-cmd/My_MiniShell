/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:29:24 by vloth             #+#    #+#             */
/*   Updated: 2023/07/10 15:47:16 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	is_meta(t_data *data)
{
	int		i;
	t_cmd	*cmd;
	int		m;

	i = 0;
	m = 0;
	cmd = data->cmdIndex->begin;
	while (cmd)
	{
		while (cmd->cmd[i])
		{
			if (cmd->cmd[i] == '$')
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
		if (str[i] == '$')
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspeciel <nspeciel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:06:02 by vloth             #+#    #+#             */
/*   Updated: 2023/09/06 18:24:07 by nspeciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*fait_le_cafe(char **test, t_data *data)
{
	char	*cmd;
	int		j;

	j = 0;
	while (test[j])
	{
		fait_le_cafe_second(test, j);
		if (j == 0)
		{
			if (!ft_valid_meta(test[j], data))
				cmd = 0;
			else
				cmd = ft_getenv(test[j], data);
		}
		else
		{
			if (!ft_valid_meta(test[j], data))
				cmd = ft_strjoin(cmd, test[j]);
			else
				cmd = ft_strjoin(cmd, ft_getenv(test[j], data));
		}
		j++;
	}
	return (cmd);
}

void	do_meta(t_data *data)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = data->cmd_index->begin;
	while (cmd)
	{
		if (cmd->have_meta)
		{
			while (cmd->argv[i])
			{
				if (is_meta_second(cmd->argv[i]) \
				&& !is_simple_quote(cmd->argv[i]))
					do_meta_second(data, i, cmd);
				i++;
			}
		}
		i = 0;
		cmd = cmd->next;
	}
}

void	cut_arg(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmd_index->begin;
	while (cmd)
	{
		if (cmd->redir)
			cmd->argv = ft_split_s(cmd->just_cmd, ' ');
		else
			cmd->argv = ft_split_s(cmd->cmd, ' ');
		cmd = cmd->next;
	}
	cmd = data->cmd_index->begin;
	int i = 0;
	while (cmd->argv[i])
		i++;
	do_meta(data);
	cut_quote(data);
}

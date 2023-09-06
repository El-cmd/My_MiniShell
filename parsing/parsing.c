/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspeciel <nspeciel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:06:02 by vloth             #+#    #+#             */
/*   Updated: 2023/09/06 22:28:21 by nspeciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*fait_le_cafe(char **test, t_data *data)
{
	int		j;
	char	*cmd;
	char	*env_value;
	char	*new_cmd;

	j = 0;
	cmd = NULL;
	while (test[j])
	{
		fait_le_cafe_second(test, j);
		if (!ft_valid_meta(test[j], data))
		{
			free(cmd);
			cmd = NULL;
		}
		else
		{
			env_value = ft_getenv(test[j], data);
			new_cmd = NULL;
			if (cmd)
			{
				new_cmd = ft_strjoin(cmd, env_value);
				free(cmd);
			}
			else
				new_cmd = ft_strdup(env_value);
			cmd = new_cmd;
			free(env_value);
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
	do_meta(data);
	cut_quote(data);
}

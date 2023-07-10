/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:06:02 by vloth             #+#    #+#             */
/*   Updated: 2023/07/10 16:07:19 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cut_quote(t_data *data)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = data->cmdIndex->begin;
	while (cmd)
	{
		if (cmd->quotes)
		{
			while (cmd->argv[i])
			{
				cmd->argv[i] = ft_strtrim(cmd->argv[i], "\"");
				cmd->argv[i] = ft_strtrim(cmd->argv[i], "\'");
				i++;
			}
			i = 0;
		}
		cmd = cmd->next;
	}
}

char	*fait_le_cafe(char **test, t_data *data)
{
	char	*cmd;
	int		j;

	j = 0;
	cmd = NULL;
	while (test[j])
	{
		test[j] = ft_strtrim(test[j], "\"");
		if (j == 0)
		{
			if (!ft_valid_meta(test[j], data))
				cmd = ft_strdup(test[j]);
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
	char	**test;

	i = 0;
	cmd = data->cmdIndex->begin;
	while (cmd)
	{
		if (cmd->have_meta)
		{
			while (cmd->argv[i])
			{
				if (is_meta_second(cmd->argv[i]) \
				&& !is_simple_quote(cmd->argv[i]))
				{
					cmd->argv[i] = ft_strtrim(cmd->argv[i], "\"");
					test = ft_split(cmd->argv[i], '$');
					cmd->argv[i] = fait_le_cafe(test, data);
				}
				i++;
			}
		}
		cmd = cmd->next;
	}
}

void	cut_arg(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmdIndex->begin;
	while (cmd)
	{
		if (cmd->redir)
			cmd->argv = ft_split(cmd->just_cmd, ' ');
		else
			cmd->argv = ft_split(cmd->cmd, ' ');
		cmd = cmd->next;
	}
	do_meta(data);
	cut_quote(data);
}

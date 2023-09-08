/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspeciel <nspeciel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:06:02 by vloth             #+#    #+#             */
/*   Updated: 2023/09/08 17:04:36 by nspeciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*combine(const char *env_var, const char *prev_cmd, t_data *data)
{
	char	*env_var_copy;
	char	*env_value;
	char	*new_cmd;

	env_var_copy = strdup(env_var);
	env_value = ft_getenv(env_var_copy, data);
	new_cmd = NULL;
	if (prev_cmd)
	{
		new_cmd = ft_strjoin(prev_cmd, env_value);
	}
	else
	{
		new_cmd = ft_strdup(env_value);
	}
	free(env_var_copy);
	free(env_value);
	return (new_cmd);
}

char	*fait_le_cafe(char **test, t_data *data)
{
	int		j;
	char	*cmd;
	char	*env_value;

	j = 0;
	cmd = NULL;
	while (test[j])
	{
		fait_le_cafe_second(test, j);
		if (!ft_valid_meta(test[j], data))
		{
			free(cmd);
			cmd = ft_strdup(test[j]);
		}
		else
		{
			env_value = combine(test[j], cmd, data);
			free(cmd);
			cmd = env_value;
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
		if (cmd->have_meta && cmd->argv)
		{
			while (cmd->argv[i])
			{
				if (is_meta_second(cmd->argv[i]))
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

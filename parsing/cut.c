/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:06:51 by vloth             #+#    #+#             */
/*   Updated: 2023/05/13 18:14:59 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cut(t_cmd *cmd, int *i)
{
	int	start;
	int	end;

	start = *i;
	while (is_redir_or_cmd(cmd->cmd[*i]) == 0 && cmd->cmd[*i] != '\0')
		(*i)++;
	end = *i;
	cmd->just_cmd = ft_substr(cmd->cmd, start, (end - start));
}

int	do_cut_one(t_cmd *cmd, int *i)
{
	(*i)++;
	pass_space(cmd->cmd, i);
	get_file(cmd->cmd, i);
	pass_space(cmd->cmd, i);
	(*i)--;
	if (is_redir_or_cmd(cmd->cmd[*i] == 0))
	{
		cut(cmd, i);
		return (1);
	}
	return (0);
}

int	do_cut_two(t_cmd *cmd, int *i)
{
	pass_space(cmd->cmd, i);
	get_file(cmd->cmd, i);
	pass_space(cmd->cmd, i);
	(*i)--;
	if (is_redir_or_cmd(cmd->cmd[*i] == 0))
	{
		cut(cmd, i);
		return (1);
	}
	return (0);
}

void	find_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmd[i])
	{
		pass_space(cmd->cmd, &i);
		if (is_redir_or_cmd(cmd->cmd[i]))
		{
			i++;
			if (is_redir_or_cmd(cmd->cmd[i]))
			{
				if (do_cut_one (cmd, &i))
					return ;
			}
			else
				if (do_cut_two(cmd, &i))
					return ;
		}
		else
		{
			cut(cmd, &i);
			return ;
		}
		i++;
	}
}

void	exec_find_cmd(t_data *data)
{
	t_cmd	*tmp;

	tmp = data->cmdIndex->begin;
	while (tmp)
	{
		if (tmp->redir == true)
			find_cmd(tmp);
		tmp = tmp->next;
	}
}

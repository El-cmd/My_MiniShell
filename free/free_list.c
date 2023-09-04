/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspeciel <nspeciel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:00:48 by nspeciel          #+#    #+#             */
/*   Updated: 2023/08/04 18:08:49 by nspeciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_cmd(t_cmd *cmd)
{
	free(cmd->cmd);
	if (cmd->redir)
	{
		free(cmd->just_cmd);
		free_redir(cmd->lredir);
	}
	free_tab(cmd->argv);
}

t_cmd	*pop_front_dlist(t_cmd_index *index)
{
	t_cmd	*tmp;

	tmp = index->begin;
	if (index->nb_cmd == 0 || index->begin == NULL)
		return (tmp);
	if (index->nb_cmd == 1)
	{
		free_cmd(tmp);
		index->begin = NULL;
		index->end = NULL;
	}
	else
	{
		free_cmd(tmp);
		index->begin = index->begin->next;
		index->begin->back = NULL;
	}
	index->nb_cmd--;
	return (tmp);
}

void	free_list(t_cmd_index *index)
{
	t_cmd	*tmp;

	tmp = index->begin;
	while (tmp)
	{
		tmp = pop_front_dlist(index);
		free(tmp);
	}
	free(index);
	index = NULL;
}

void	free_list_second(t_data *data)
{
	t_cmd	*tmp;

	tmp = data->cmd_index->begin;
	while (tmp)
	{
		tmp = pop_front_dlist(data->cmd_index);
		free(tmp);
	}
}

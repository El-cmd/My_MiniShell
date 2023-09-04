/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspeciel <nspeciel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:25:38 by vloth             #+#    #+#             */
/*   Updated: 2023/08/30 01:24:21 by nspeciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*pop_front_dlist_env(t_env_som *index)
{
	t_env	*tmp;

	tmp = index->begin;
	if (index->size == 0)
		return (tmp);
	if (index->size == 1)
	{
		free(tmp->name);
		free(tmp->name_split);
		free(tmp->value_split);
		index->begin = NULL;
		index->end = NULL;
	}
	else
	{
		free(tmp->name);
		free(tmp->name_split);
		free(tmp->value_split);
		index->begin = index->begin->next;
		index->begin->back = NULL;
	}
	index->size--;
	return (tmp);
}

void	data_env(t_data *data)
{
	t_env	*tmp;

	tmp = data->env->begin;
	while (tmp)
	{
		tmp = pop_front_dlist_env(data->env);
		free(tmp);
	}
	free(data->env);
}

t_redir	*pop_front_dlist_redir(t_redirindex *redir)
{
	t_redir	*tmp;

	tmp = redir->begin;
	if (redir->size == 0)
		return (tmp);
	if (redir->size == 1)
	{
		free(tmp->file);
		redir->begin = NULL;
		redir->end = NULL;
	}
	else
	{
		free(tmp->file);
		redir->begin = redir->begin->next;
		redir->begin->back = NULL;
	}
	redir->size--;
	return (tmp);
}

void	free_redir(t_redirindex *redir)
{
	t_redir	*tmp;

	tmp = redir->begin;
	while (tmp)
	{
		tmp = pop_front_dlist_redir(redir);
		free(tmp);
	}
	free(redir);
}

void	free_everything(t_data *data)
{
	data_env(data);
	if (data->cmd_index)
		free_list(data->cmd_index);
	if (data->path_exec != NULL)
		free_tab(data->path_exec);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:25:38 by vloth             #+#    #+#             */
/*   Updated: 2023/05/13 18:25:39 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
t_cmd 	*pop_front_dlist(t_cmdIndex *index);
void	free_list(t_cmdIndex *index);
void	free_tab(char **str);
*/

t_cmd *pop_front_dlist(t_cmdIndex *index)
{
	t_cmd *tmp;

	tmp = index->begin;
	if (index->nb_cmd == 1)
	{
		free(tmp->cmd);
		index->begin = NULL;
		index->end = NULL;
	}
	else
	{
		free(tmp->cmd);
		index->begin = index->begin->next;
		index->begin->back = NULL;
	}
	index->nb_cmd--;
	return (tmp);
}

void	free_list(t_cmdIndex *index)
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

void	free_tab(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

t_env *pop_front_dlist_env(t_envSom *index)
{
	t_env *tmp;

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


//t_env	*pop_front_dlist_env(t_envSom *l)
//{
//	t_env *tmp;
//
//	tmp = l->begin;
//	if (l->size > 1)
//	{
//		free(tmp->name);
//		free(tmp->name_split);
//		free(tmp->value_split);
//		tmp = l->begin;
//		l->begin = l->begin->next;
//		l->begin->back = NULL;
//		l->size--;
//	}
//	else
//	{
//		free(tmp->name);
//		free(tmp->name_split);
//		free(tmp->value_split);
//		tmp = l->begin;
//		l->begin = NULL;
//		l->end = NULL;
//		l->size = 0;
//	}
//	return (tmp);
//}

void data_env(t_data *data)
{
	t_env *tmp;

	tmp = data->env->begin;
	while (tmp)
	{
		tmp = pop_front_dlist_env(data->env);
		free(tmp);
	}
	free(data->env);
	data->env = NULL;
}
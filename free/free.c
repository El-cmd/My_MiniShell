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
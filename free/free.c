#include "../minishell.h"

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
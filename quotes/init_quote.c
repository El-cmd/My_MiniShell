/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:10:15 by vloth             #+#    #+#             */
/*   Updated: 2023/07/10 16:11:42 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_quIndex	*init_quote(void)
{
	t_quIndex	*quIndex;

	quIndex = malloc(sizeof(t_quIndex));
	if (!quIndex)
		exit(EXIT_FAILURE);
	quIndex->begin = NULL;
	quIndex->end = NULL;
	quIndex->size = 0;
	return (quIndex);
}

void	pushback_quote(char *str, t_quIndex *quIndex)
{
	t_quote	*element;

	element = malloc(sizeof(t_quote));
	if (!element)
		exit(EXIT_FAILURE);
	element->str = str;
	element->next = NULL;
	element->back = NULL;
	if (quIndex->size == 0)
	{
		quIndex->begin = element;
		quIndex->end = element;
	}
	else
	{
		quIndex->end->next = element;
		element->back = quIndex->end;
		quIndex->end = element;
	}
	quIndex->size++;
}

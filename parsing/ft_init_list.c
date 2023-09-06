/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspeciel <nspeciel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:25:01 by vloth             #+#    #+#             */
/*   Updated: 2023/09/06 22:27:55 by nspeciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd_index	*init_cmd(void)
{
	t_cmd_index	*cmd_index;

	cmd_index = malloc(sizeof(t_cmd_index));
	if (!cmd_index)
		exit(EXIT_FAILURE);
	cmd_index->begin = NULL;
	cmd_index->end = NULL;
	cmd_index->nb_cmd = 0;
	cmd_index->nb_pipe = 0;
	return (cmd_index);
}

//tout est dans le nom ne pas oublier de mettre le type
void	pushback_cmd(char *cmd, t_cmd_index *cmd_index, int quote)
{
	t_cmd	*element;

	element = malloc(sizeof(t_cmd));
	if (!element)
		exit(EXIT_FAILURE);
	element->cmd = ft_strdup(cmd);
	if (quote)
		element->quotes = true;
	else
		element->quotes = false;
	element->just_cmd = ft_strdup("");
	element->next = NULL;
	element->back = NULL;
	if (cmd_index->nb_cmd == 0)
	{
		cmd_index->begin = element;
		cmd_index->end = element;
	}
	else
	{
		cmd_index->end->next = element;
		element->back = cmd_index->end;
		cmd_index->end = element;
		cmd_index->nb_pipe++;
	}
	cmd_index->nb_cmd++;
}

//print les commande
void	print_list(t_cmd_index *cmd_index)
{
	t_cmd	*p;

	p = cmd_index->begin;
	while (p)
	{
		printf("%s\n", p->cmd);
		p = p->next;
	}
}

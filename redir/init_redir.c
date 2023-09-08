/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:24:45 by vloth             #+#    #+#             */
/*   Updated: 2023/09/08 13:10:29 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redirindex	*init_redir_i(void)
{
	t_redirindex	*redir_i;

	redir_i = malloc(sizeof(t_redirindex));
	if (!redir_i)
		exit (EXIT_FAILURE);
	redir_i->begin = NULL;
	redir_i->end = NULL;
	redir_i->size = 0;
	return (redir_i);
}

void	pushback_redir(t_redirindex *i, int type, int index, char *str)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		exit(EXIT_FAILURE);
	redir->type = type;
	begin_end_file(index, redir, str);
	redir->next = NULL;
	redir->back = NULL;
	if (i->size == 0)
	{
		i->begin = redir;
		i->end = redir;
	}
	else
	{
		i->end->next = redir;
		redir->back = i->end;
		i->end = redir;
	}
	i->size++;
}

// parse pour voir si dans la cmd il y a des redirection
int	look_if_redir(char *line)
{
	int	i;
	int q;

	i = 0;
	q = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			i = parseur_quotes(line, i + 1, line[i]);
			if (i == -1 && q == 1)
				return (1);
			else if (i == -1 && q == 0)
				return (0);
		}
		else if (line[i] == '<' || line[i] == '>')
			q = 1;
		i++;
	}
	if (q == 1)
		return (1);
	return (0);
}

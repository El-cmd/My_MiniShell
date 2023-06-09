/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:24:45 by vloth             #+#    #+#             */
/*   Updated: 2023/07/10 16:26:39 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redirIndex	*init_redirI(void)
{
	t_redirIndex	*redirI;

	redirI = malloc(sizeof(t_redirIndex));
	if (!redirI)
		exit (EXIT_FAILURE);
	redirI->begin = NULL;
	redirI->end = NULL;
	redirI->size = 0;
	return (redirI);
}

void	pushback_redir(t_redirIndex *i, int type, int index, char *str)
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
int	lookIfRedir(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '"' || line[i] == '\'')
			i = parseur_quotes(line, i + 1, line[i]);
		else if (line[i] == '<' && line[i + 1] == '<')
			return (1);
		else if (line[i] == '<')
			return (1);
		else if (line[i] == '>' && line[i + 1] == '>')
			return (1);
		else if (line[i] == '>')
			return (1);
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:24:42 by vloth             #+#    #+#             */
/*   Updated: 2023/05/13 18:24:43 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
void	redirOrNot(t_cmdIndex *index);
void	initRedirOrnot(t_cmdIndex *index);
int 	malloc_out(char *str, int *i, t_redirIndex *tmp);
int 	malloc_in(char *str, int *i, t_redirIndex *tmp);
int 	malloc_redir(t_data *data);
*/
// regarde si il y a des redirection ou non et remplie le token
void	redirOrNot(t_cmdIndex *index)
{
	t_cmd *tmp;

	tmp = index->begin;
	while (tmp)
	{
		if (lookIfRedir(tmp->cmd) == 1)
			tmp->redir = true;
		else
			tmp->redir = false;
		tmp = tmp->next;
	}
}

// init la liste chainé des redirection pour chaque cmd
// si il y a des redirection
void	initRedirOrnot(t_cmdIndex *index)
{
	t_cmd *tmp;

	tmp = index->begin;
	while (tmp)
	{
		if (tmp->redir == true)
			tmp->lredir = init_redirI();
		else
			tmp->lredir = NULL;
		tmp = tmp->next;
	}
}

//parsing des redirections out
int malloc_out(char *str, int *i, t_redirIndex *tmp)
{
	if (str[*i] == '>')
	{
		*i = *i + 1;
		if (str[*i] == '>')
		{
			*i = *i + 1;
			pass_space(str, i);
			if (is_end_redir(str[*i]) == 1)
				return(EXIT_FAILURE);
			pushback_redir(tmp, APPEND, *i, str);
		}
		else
		{
			pass_space(str, i);
			if (is_end_redir(str[*i]) == 1)
				return(EXIT_FAILURE);
			pushback_redir(tmp, R_OUT, *i, str);
		}
	}
	return (0);
}

//parsing des redirections in
int malloc_in(char *str, int *i, t_redirIndex *tmp)
{
	if (str[*i] == '<')
	{
		*i = *i + 1;
		if (str[*i] == '<')
		{
			*i = *i + 1;
			pass_space(str, i);
			if (is_end_redir(str[*i]) == 1)
				return(EXIT_FAILURE);
			pushback_redir(tmp, HERD, *i, str);
		}
		else
		{
			pass_space(str, i);
			if (is_end_redir(str[*i]) == 1)
				return(EXIT_FAILURE);
			pushback_redir(tmp, R_IN, *i, str);
		}
	}
	return (0);
}

// malloc la liste chainé des redirection attention les <> et ><
int malloc_redir(t_data *data)
{
	int i;
	t_cmd *tmp;

	tmp = data->cmdIndex->begin;
	while (tmp)
	{
		if (tmp->redir == true)
		{
			i = 0;
			while (tmp->cmd[i])
			{
				if (malloc_out(tmp->cmd, &i, tmp->lredir) == 1)
					return (EXIT_FAILURE);
				else if (malloc_in(tmp->cmd, &i, tmp->lredir) == 1)
					return (EXIT_FAILURE);
				i++;
			}
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
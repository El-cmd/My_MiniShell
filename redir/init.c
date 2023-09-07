/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:24:42 by vloth             #+#    #+#             */
/*   Updated: 2023/09/07 20:50:22 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redir_or_not(t_cmd_index *index)
{
	t_cmd	*tmp;

	tmp = index->begin;
	while (tmp)
	{
		if (!look_if_redir(tmp->cmd))
			tmp->redir = true;
		else
			tmp->redir = false;
		tmp = tmp->next;
	}
}

void	init_redir_or_not(t_cmd_index *index)
{
	t_cmd	*tmp;

	tmp = index->begin;
	while (tmp)
	{
		if (tmp->redir == true)
			tmp->lredir = init_redir_i();
		else
			tmp->lredir = NULL;
		tmp = tmp->next;
	}
}

//parsing des redirections out
int	malloc_out(char *str, int *i, t_redirindex *tmp)
{
	if (str[*i] == '>')
	{
		*i = *i + 1;
		if (str[*i] == '>')
		{
			*i = *i + 1;
			pass_space(str, i);
			if (is_end_redir(str[*i]) == 1)
				return (EXIT_FAILURE);
			pushback_redir(tmp, APPEND, *i, str);
		}
		else
		{
			pass_space(str, i);
			if (is_end_redir(str[*i]) == 1)
				return (EXIT_FAILURE);
			pushback_redir(tmp, R_OUT, *i, str);
		}
	}
	return (0);
}

//parsing des redirections in
int	malloc_in(char *str, int *i, t_redirindex *tmp)
{
	if (str[*i] == '<')
	{
		*i = *i + 1;
		if (str[*i] == '<')
		{
			*i = *i + 1;
			pass_space(str, i);
			if (is_end_redir(str[*i]) == 1)
				return (EXIT_FAILURE);
			pushback_redir(tmp, HERD, *i, str);
		}
		else
		{
			pass_space(str, i);
			if (is_end_redir(str[*i]) == 1)
				return (EXIT_FAILURE);
			pushback_redir(tmp, R_IN, *i, str);
		}
	}
	return (0);
}

// malloc la liste chainé des redirection attention les <> et ><
int	malloc_redir(t_data *data)
{
	int		i;
	t_cmd	*tmp;

	tmp = data->cmd_index->begin;
	while (tmp)
	{
		if (tmp->redir == true)
		{
			i = 0;
			while (tmp->cmd[i])
			{
				if (tmp->cmd[i] == '"' || tmp->cmd[i] == '\'')
					i = parseur_quotes(tmp->cmd, i + 1, tmp->cmd[i]);
				else if (malloc_out(tmp->cmd, &i, tmp->lredir) == 1)
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

#include "../minishell.h"

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
// can use one f() like this: int redirection(char *str, int *i, t_redirIndex *tmp, char r)
int balade_out(char *str, int *i, t_redirIndex *tmp)
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
			pushback_redir(tmp);
		}
		else
		{
			pass_space(str, i);
			if (is_end_redir(str[*i]) == 1)
				return(EXIT_FAILURE);
			pushback_redir(tmp);
		}
	}
	return (0);
}

//parsing des redirections in
int ballad_in(char *str, int *i, t_redirIndex *tmp)
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
			pushback_redir(tmp);
		}
		else
		{
			pass_space(str, i);
			if (is_end_redir(str[*i]) == 1)
				return(EXIT_FAILURE);
			pushback_redir(tmp);
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
				//if (redirection(tmp->cmd, &i, tmp->lredir, '>') == 1)
				if (balade_out(tmp->cmd, &i, tmp->lredir) == 1)
					return (EXIT_FAILURE);
				else if (ballad_in(tmp->cmd, &i, tmp->lredir) == 1)
					return (EXIT_FAILURE);
				i++;
			}
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
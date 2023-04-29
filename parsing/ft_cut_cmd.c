#include "../minishell.h"

int	ft_pipeError(char *line)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '|')
		{
			if (line[i + 1] == '|')
				return (1);
			if (line[i + 1] == '\0')
				return (1);
			j++;
		}
		i++;
	}
	if (j > 0)
		return (0);
	return (2);
}

void	splitage(char *line, t_cmdIndex *cmdIndex)
{
	char	**line_second;
	int i;

	i = 0;
	line_second = ft_split(line, '|');
	while (line_second[i])
	{
		line_second[i] = ft_strtrim(line_second[i], " ");
		i++;
	}
	i = 0;
	while (line_second[i])
	{
		pushback_cmd(line_second[i], cmdIndex);
		i++;
	}
}

void	splitOrNot(char *line, t_cmdIndex *cmdIndex)
{
	if (ft_pipeError(line) == 1)
		return ;
	else if (ft_pipeError(line) == 2)
		pushback_cmd(line, cmdIndex);
	else if (ft_pipeError(line) == 0)
		splitage(line, cmdIndex);
}

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


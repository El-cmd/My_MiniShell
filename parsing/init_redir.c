#include "../minishell.h"

t_redirIndex	*init_redirI(void)
{
	t_redirIndex *redirI;

	redirI = malloc(sizeof(t_redirIndex));
	if (!redirI)
		exit(EXIT_FAILURE);
	redirI->begin = NULL;
	redirI->end = NULL;
	redirI->size = 0;
	return (redirI);
}

void	pushback_redir(t_redirIndex *i)
{
	t_redir *redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		exit(EXIT_FAILURE);
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

int lookIfRedir(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '<' && line[i + 1] == '<')
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
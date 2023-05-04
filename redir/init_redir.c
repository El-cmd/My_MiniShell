#include "../minishell.h"

//init le sommaire de la liste chaine des redir
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


//tout est dans le nom ne pas oublier de mettre le type
//et de parser le file 
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

// parse pour voir si dans la cmd il y a des redirection
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
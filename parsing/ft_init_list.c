#include "../minishell.h"

t_cmdIndex *init_cmd(void)
{
	t_cmdIndex *cmdIndex;

	cmdIndex = malloc(sizeof(t_cmdIndex));
	if (!cmdIndex)
		exit(EXIT_FAILURE);
	cmdIndex->begin = NULL;
	cmdIndex->end = NULL;
	cmdIndex->nb_cmd = 0;
	cmdIndex->nb_pipe = 0;
	return (cmdIndex);
}

void pushback_cmd(char *cmd, t_cmdIndex *cmdIndex)
{
	t_cmd *element;

	element = malloc(sizeof(t_cmd));
	if (!element)
		exit(EXIT_FAILURE);
	element->cmd = cmd;
	element->next = NULL;
	element->back = NULL;
	if (cmdIndex->nb_cmd == 0)
	{
		cmdIndex->begin = element;
		cmdIndex->end = element;
	}
	else
	{
		cmdIndex->end->next = element;
		element->back = cmdIndex->end;
		cmdIndex->end = element;
		cmdIndex->nb_pipe++;
	}
	cmdIndex->nb_cmd++;
}

void print_list(t_cmdIndex *cmdIndex)
{
	t_cmd *p;

	p = cmdIndex->begin;
	while (p)
	{
		printf("%s\n", p->cmd);
		p = p->next;
	}
}


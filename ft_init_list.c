#include "minishell.h"

void push(t_cmd **p, char *line)
{
        t_cmd *element = malloc(sizeof(t_cmd));
        if(!element)
			exit(EXIT_FAILURE);
        element->cmd = line;
        element->next = *p;
        *p = element;
}

void print_list(t_cmd *p)
{
	while(p->next)
	{
			printf("%s\n", p->cmd);
			p = p->next;
	}
}
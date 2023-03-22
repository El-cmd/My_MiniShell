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

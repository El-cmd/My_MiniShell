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

void 	push_second(t_token_cmd *cmd)
{
	t_token_cmd *element;
	
	element = malloc(sizeof(t_token_cmd));
	if(!element)
		exit(EXIT_FAILURE);
	if (!cmd)
	{
		cmd = element;
		cmd->next = NULL;
	}
	else
	{
		cmd->next = element;
		element->next = NULL;
	}
}

void 	init_token_cmd(t_cmd *cmds)
{
	t_token_cmd *token_cmds;

	token_cmds = NULL;
	while (cmds->next)
	{
		push_second(token_cmds);
		cmds = cmds->next;
	}
}

void make_list(char **line_second)
{
	t_cmd *cmds;
	cmds = NULL;
	int i = 0;
	while (line_second[i])
		i++;
	while (i >= 0)
	{
		push(&cmds, line_second[i]);
		i--;
	}
	print_list(cmds);
	init_token_cmd(cmds);
}

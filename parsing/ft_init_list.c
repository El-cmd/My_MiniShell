#include "../minishell.h"

void push(t_cmd **p, char *line)
{
    t_cmd *element;

	element = malloc(sizeof(t_cmd));
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

void 	push_second(t_token_cmd **cmd)
{
	t_token_cmd *element;
	
	element = malloc(sizeof(t_token_cmd));
	if(!element)
		exit(EXIT_FAILURE);
	element->HereDoc = 0;
	element->inRedirection = 0;
	element->appendRedirection = 0;
	element->outRedirection = 0;
	element->next = *cmd;
	*cmd = element;
}

t_token_cmd *init_token_cmd(t_cmd *cmds)
{
	t_token_cmd *token_cmds;

	token_cmds = NULL;
	while (cmds->next)
	{
		push_second(&token_cmds);
		cmds = cmds->next;
	}
	return (token_cmds);
}

void make_list(char **line_second, t_token_line *prout, char **envp, t_envSom *doberman)
{
	t_cmd *cmds;
	t_token_cmd *token_cmd;

	token_cmd = NULL;
	cmds = NULL;
	int i = 0;
	while (line_second[i])
		i++;
	while (i >= 0)
	{
		push(&cmds, line_second[i]);
		i--;
	}
	token_cmd = init_token_cmd(cmds);
	token(token_cmd, cmds);
	simple_cmd(token_cmd, prout, doberman, cmds, envp);
}

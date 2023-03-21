#include "minishell.h"

t_cmd init_t_cmd(void)
{
	t_cmd cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
	{
		perror("Malloc failure\n");
		return (NULL);
	}
	cmd->cmd = NULL;
	cmd->next = NULL;
	return (cmd);
}

void push(char *line_cmd, t_cmd *cmd)
{
	t_cmd *element;

	element = malloc(sizeof(*element));
	if (element == NULL)
		return ;
	if (cmd == NULL)
		cmd = element;
	element->cmd = line_cmd;
	cmd->next = element;
}

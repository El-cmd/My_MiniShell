#include "minishell.h"

int	redir_compteur(t_token_cmd *cmd, char *line, int i)
{
	while(line[i] != '\0')
	{
		if (line[i] == '<' && line[i + 1] == '<')
		{
			i+=2;
			cmd->HereDoc++;
			return (i);
		}
		else if (line[i] == '<')
		{
			i++;
			cmd->inRedirection++;
			return (i);
		}
		else if (line[i] == '>' && line[i + 1] == '>')
		{
			i+=2;
			cmd->appendRedirection++;
			return (i);
		}
		else if (line[i] == '>')
		{
			i++;
			cmd->outRedirection++;
			return (i);
		}
		i++;
	}
	return(-1);
}

void token(t_token_cmd *cmd, t_cmd *cmds)
{
	int i;

	i = 0;
	while(cmds->next)
	{
		i = 0;
		while(i != -1)
			i = redir_compteur(cmd, cmds->cmd, i);
		cmd = cmd->next;
		cmds = cmds->next;
	}
}

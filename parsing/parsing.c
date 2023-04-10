#include "../minishell.h"

//int	redir_compteur(t_token_cmd *cmd, char *line, int i)
//{
//	while(line[i] != '\0')
//	{
//		if (line[i] == '<' && line[i + 1] == '<')
//		{
//			i+=2;
//			cmd->HereDoc++;
//			return (i);
//		}
//		else if (line[i] == '<')
//		{
//			i++;
//			cmd->inRedirection++;
//			return (i);
//		}
//		else if (line[i] == '>' && line[i + 1] == '>')
//		{
//			i+=2;
//			cmd->appendRedirection++;
//			return (i);
//		}
//		else if (line[i] == '>')
//		{
//			i++;
//			cmd->outRedirection++;
//			return (i);
//		}
//		i++;
//	}
//	return(-1);
//}
//

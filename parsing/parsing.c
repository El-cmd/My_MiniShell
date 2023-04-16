#include "../minishell.h"

//int	redir_compteur(char *line)
//{
//	int i;
//	t_redirIndex *in;
//
//	i = 0;
//	in = init_redirI();
//	while(line[i] != '\0')
//	{
//		if (line[i] == '<' && line[i + 1] == '<')
//		{
//			i+=2;
//			return (i);
//		}
//		else if (line[i] == '<')
//		{
//			i++;
//			return (i);
//		}
//		else if (line[i] == '>' && line[i + 1] == '>')
//		{
//			i+=2;
//			return (i);
//		}
//		else if (line[i] == '>')
//		{
//			i++;
//			return (i);
//		}
//		i++;
//	}
//	return(-1);
//}
//

#include "minishell.h"

t_token_line *ft_tk_line(char *line)
{
	t_token_line *tk_line;
	
	tk_line = malloc(sizeof(t_token_line));
	if (!tk_line)
	{
		perror("Malloc failure\n");
		return (NULL);
	}
	tk_line->nb_cmd = 1;
	tk_line->nb_pipe = 0;
	while (*line)
	{
		if (*line == '|')
		{
			tk_line->nb_cmd++;
			tk_line->nb_pipe++;
		}
		line++;
	}
	return (tk_line);
}
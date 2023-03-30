#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	const char *line;
	char **line_second;
	line = malloc(sizeof(char *) * BUFFER_SIZE_MAX);
	t_token_line *prout;
	t_envSom *doberman = init_envp(envp);
	prout = NULL;
	if (!line)
	{
		perror("Malloc failure\n");
		return (EXIT_FAILURE);
	}
	while(1)
	{
		line = readline( "MS >> 🤖: " );
		prout = ft_tk_line((char *)line);
		line_second = ft_init_char((char *)line);
		make_list(line_second, prout, envp, doberman);
		add_history(line);
		free((void*)line);
		free(prout);
	}
	return (0);
}
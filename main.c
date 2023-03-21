#include "minishell.h"

int main(void)
{
	const char *line;
	char **line_second;
	line = malloc(sizeof(char *) * BUFFER_SIZE_MAX);
	if (!line)
	{
		perror("Malloc failure\n");
		return (EXIT_FAILURE);
	}
	while(1)
	{
		line = readline( "MS >> 🤖: " );
		t_token_line *prout = ft_tk_line((char *)line);
		printf("nb de cmd: %d\nnb de pipe %d\n", prout->nb_cmd, prout->nb_pipe);
		printf("%s\n", line);
		line_second = ft_init_char((char *)line);
		while(*line_second)
		{
			printf("%s\n", *line_second);
			line_second++;
		}

		add_history(line);
		free((void*)line);
		free(prout);
	}
	return (0);
}
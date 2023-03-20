#include "minishell.h"

int main(void)
{
	char *line;
	line = malloc(sizeof(char *) * BUFFER_SIZE_MAX);
	if (!line)
	{
		perror("Malloc failure\n");
		return (EXIT_FAILURE);
	}
	while(1)
	{
		line = readline( "MS >> 🤖: " );
		printf("%s\n", line);
		add_history(line);
		free(line);
	}
	return (0);
}
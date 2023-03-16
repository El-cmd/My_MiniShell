#include "minishell.h"

int main(void)
{
	char *line;
	line = malloc(sizeof(char) * 1024);
	line = readline( "test> " );
	printf("%s\n", line);
	free(line);
	return (0);
}
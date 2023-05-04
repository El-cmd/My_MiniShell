#include "../minishell.h"

// Gestion des arguments
void the_arg(int ac, char **av)
{
	(void)av;
	if (ac != 1)
		exit(EXIT_FAILURE);
}

// Gestion des erreur de malloc
int	malloc_error(char *str)
{
	if (!str)
	{
		perror("Malloc failure\n");
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

//fork error
pid_t fork_error(void)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Fork failure\n");
		exit(EXIT_FAILURE);
	}
	return (pid);
}
#include "..\minishell.h"

pid_t	new_process()
{
	pid_t	pid;
	pid = fork();
	return pid;
}


#include "../minishell.h"

void ft_simple_pipe(t_cmdIndex *index, char **envp)
{
	pid_t pid;
	pid_t pid2;
	int fd[2];
	int status;

	if (index->nb_pipe == 1)
	{
		pid2 = fork();
		if (pid2 == 0)
		{
			pipe(fd);
			pid = fork();
			if (pid == 0)
			{
				dup2(fd[1], IN);
				close(fd[0]);
				close(fd[1]);
				ft_execve(index->begin->cmd, envp);
			}
			else
			{
				dup2(fd[0], OUT);
				close(fd[0]);
				close(fd[1]);
				waitpid(pid, &status, 0);
				ft_execve(index->end->cmd, envp);
			}
		}
		else
			waitpid(pid2, &status, 0);
	}
}

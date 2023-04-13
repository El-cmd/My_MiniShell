#include "../minishell.h"

void ft_simple_pipe(t_cmdIndex *index, char **envp, t_envSom *env)
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
				close(fd[0]);
				dup2(fd[1], IN);
				close(fd[1]);
				if (ft_builtins(index->begin, env) == 0)
					exit(0);
				ft_execve(index->begin->cmd, envp);
			}
			else
			{
				close(fd[1]);
				dup2(fd[0], OUT);
				close(fd[0]);
				waitpid(pid, &status, 0);
				if (ft_builtins(index->end, env) == 0)
					exit(0);
				ft_execve(index->end->cmd, envp);
			}
		}
		else
			waitpid(pid2, &status, 0);
	}
}

void multi_pipe(t_cmdIndex *index, char **envp, t_envSom *env)
{
	pid_t	pid;
	int		fd[2];
	pid_t	pid2;
	int		status;
	int		status2;
	t_cmd	*cmd;

	cmd = index->begin;
	pid = fork();
	if (pid == 0)
	{
		while (cmd)
		{
			if (cmd->next != NULL)
				pipe(fd);
			pid2 = fork();
			if (pid2 == 0)
			{
				close(fd[0]);
				dup2(fd[1], IN);
				close(fd[1]);
				if (ft_builtins(cmd, env) == 0)
					exit(0);
				ft_execve(cmd->cmd, envp);
			}
			else
			{
				if (cmd->next != NULL)
				{
					close(fd[1]);
					dup2(fd[0], OUT);
					close(fd[0]);
					close(fd[1]);
					waitpid(pid2, &status2, 0);
				}
				else
				{
					close(fd[1]);
					dup2(fd[0], OUT);
					close(fd[0]);
					waitpid(pid2, &status2, 0);
					if (ft_builtins(cmd, env) == 0)
						exit(0);
					ft_execve(cmd->cmd, envp);
				}
			}
			cmd = cmd->next;
		}
	}
	else
		waitpid(pid, &status, 0);
}
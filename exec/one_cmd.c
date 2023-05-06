#include "../minishell.h"

//execution dune seule cmd sans redirection ou pipe
int	simple_cmd(t_envSom *env, t_cmd *cmd, char **envp, t_cmdIndex *cmdIndex)
{
	pid_t pid;

	if (cmdIndex->nb_cmd == 1)
	{
		if (ft_builtins(cmd, env) == 0)
			return (0);
		pid = fork();
		if (pid == 0)
			ft_execve(cmd->cmd, envp);
		else
			wait(NULL);
	}
	return 0;
}


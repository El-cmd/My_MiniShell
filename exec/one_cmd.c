#include "../minishell.h"

void ft_execve(char *cmd, char **envp)
{
	char **cmdarg;
	int y;

	y = 0;
	cmdarg = ft_split(cmd, ' ');
	while (envp[++y])
		execve(ft_strjoin(ft_strjoin(envp[y], "/"), cmdarg[0]), cmdarg, envp);
}

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

void exec(t_cmdIndex *cmd, char **envp, t_envSom *doberman)
{
	t_cmd *tmp;

	tmp = cmd->begin;
	simple_cmd(doberman, tmp, envp, cmd);
}

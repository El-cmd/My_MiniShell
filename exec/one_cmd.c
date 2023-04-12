#include "../minishell.h"

void ft_execve(char *cmd, char **envp)
{
	char **cmdarg;
	int y;
	char *exec;

	y = 0;
	cmdarg = ft_split(cmd, ' ');
	while (envp[++y])
	{
		exec = ft_strjoin(ft_strjoin(envp[y], "/"), cmdarg[0]);
		execve(exec, cmdarg, envp);
		free(exec);
	}
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
	if (cmd->nb_cmd == 1)
		simple_cmd(doberman, tmp, envp, cmd);
	else if (cmd->nb_cmd == 2)
		ft_simple_pipe(cmd, envp, doberman);
}

#include "../minishell.h"

// fonction d'execution
void ft_execve(char *cmd, char **envp)
{
	char **cmdarg;
	int y;
	char *exec;

	no_str(cmd);
	y = 0;
	cmdarg = ft_split(cmd, ' ');
	while (envp[++y])
	{
		exec = ft_strjoin(ft_strjoin(envp[y], "/"), cmdarg[0]);
		execve(exec, cmdarg, envp);
		free(exec);
	}
	ft_putstr_fd(cmdarg[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	free_tab(cmdarg);
	exit(127);
}

//regarde quel execution faire si une ou plusieur cmd
void exec(t_cmdIndex *cmd, char **envp, t_envSom *doberman)
{
	t_cmd *tmp;

	tmp = cmd->begin;
	if (cmd->begin->redir == true)
		return ;
	if (cmd->nb_cmd == 1)
		simple_cmd(doberman, tmp, envp, cmd);
	else if (cmd->nb_cmd == 2)
		ft_simple_pipe(cmd, envp, doberman);
	else if (cmd->nb_cmd > 2)
		multi_pipe(cmd, envp, doberman);
}
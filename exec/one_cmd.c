#include "../minishell.h"

int	ft_builtins(t_cmd *cmd, char **envp)
{
	if (ft_strncmp(cmd->cmd, "env", 3) == 0 && ft_strlen(cmd->cmd) == 3)
	{
		ft_env(envp);
		return 0;
	}
	else if (ft_strncmp(cmd->cmd, "pwd", 3) == 0 && ft_strlen(cmd->cmd) == 3)
	{
		ft_pwd();
		return 0;
	}
	else if (ft_strncmp(cmd->cmd, "cd", 2) == 0)
	{
		ft_cd(cmd);
		return 0;
	}
	return -1;
}

void	simple_cmd(t_token_cmd *tk_cmd, t_token_line *tk_line, char **envp, t_cmd *cmds)
{
	char *exec;
	char **path;
	pid_t pid;
	char **cmdarg;
	int y;

	y = 0;
	path = ft_parsing(envp);
	if (tk_line->nb_pipe == 0 && tk_cmd->outRedirection == 0 && tk_cmd->inRedirection == 0 
		&& tk_cmd->appendRedirection == 0 && tk_cmd->HereDoc == 0)
	{	
		if (ft_builtins(cmds, envp) == 0)
			return ;
		pid = fork();
		cmdarg = ft_split(cmds->cmd, ' ');
		if (pid == 0)
		{
			while (path[++y])
			{
				exec = ft_strjoin(ft_strjoin(path[y], "/"), cmdarg[0]);
				execve(exec, cmdarg, envp);
				free(exec);
			}
		}
		else
			wait(NULL);
	}
}



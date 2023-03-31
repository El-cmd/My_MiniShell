#include "../minishell.h"

int	ft_builtins(t_cmd *cmd, t_envSom *env)
{
	if (ft_strncmp(cmd->cmd, "env", 3) == 0 && ft_strlen(cmd->cmd) == 3)
	{
		ft_env(env);
		return 0;
	}
	else if (ft_strncmp(cmd->cmd, "pwd", 3) == 0 && ft_strlen(cmd->cmd) == 3)
	{
		ft_pwd();
		return 0;
	}
	else if (ft_strncmp(cmd->cmd, "cd", 2) == 0)
	{
		ft_cd(cmd, env);
		return 0;
	}
	else if (ft_strncmp(cmd->cmd, "echo", 4) == 0)
	{
		ft_echo(cmd);
		return 0;
	}
	else if (ft_strncmp(cmd->cmd, "exit", 4) == 0 && ft_strlen(cmd->cmd) == 4)
		ft_exit();
	else if (ft_strncmp(cmd->cmd, "export", 6) == 0)
	{
		ft_export(env, cmd);
		return 0;
	}
	else if (ft_strncmp(cmd->cmd, "unset", 5) == 0)
	{
		ft_unset(env, cmd);
		return 0;
	}
	return 1;
}

void	simple_cmd(t_token_cmd *tk_cmd, t_token_line *tk_line, t_envSom *env, t_cmd *cmds, char **envp)
{
	char *exec;
	char **path;
	pid_t pid;
	char **cmdarg;
	int y;

	y = 0;
	path = ft_parsing(env);
	if (tk_line->nb_pipe == 0 && tk_cmd->outRedirection == 0 && tk_cmd->inRedirection == 0 
		&& tk_cmd->appendRedirection == 0 && tk_cmd->HereDoc == 0)
	{	
		if (ft_builtins(cmds, env) == 0)
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

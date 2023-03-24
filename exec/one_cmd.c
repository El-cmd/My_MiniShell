#include "../minishell.h"

void	simple_cmd(t_token_cmd *tk_cmd, t_token_line *tk_line, char **envp, t_cmd *cmds)
{
	char *exec;
	char **path;
	int fd[2];
	pid_t pid;
	int fdd = 0;
	char **cmdarg;
	int y;

	y = 0;
	path = ft_parsing(envp);
	if (tk_line->nb_pipe == 0 && tk_cmd->outRedirection == 0 && tk_cmd->inRedirection == 0 
		&& tk_cmd->appendRedirection == 0 && tk_cmd->HereDoc == 0)
	{
		pipe(fd);
		pid = fork();
		cmdarg = ft_split(cmds->cmd, ' ');
		if (pid == 0)
		{
			dup2(fdd, 0);
			close(fd[0]);
			while (path[++y])
			{
				exec = ft_strjoin(ft_strjoin(path[y], "/"), cmdarg[0]);
				execve(exec, cmdarg, envp);
				free(exec);
			}
		}
		else
		{
			wait(NULL);
			close(fd[1]);
			fdd = fd[0];
		}
	}
}


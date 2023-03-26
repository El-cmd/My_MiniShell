#include "../minishell.h"

int settings_cd(t_cmd *cmd)
{
	int i;

	i = 2;
	while (cmd->cmd[i] == ' ')
		i++;
	if (cmd->cmd[i] == '\0')
		return (0);
	return (1);
}

void	ft_cd(t_cmd *cmd)
{
	char *path;

	if (settings_cd(cmd) == 0)
		path = getenv("HOME");
	else
		path = cmd->cmd + 3;
	if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putendl_fd(path, 2);
	}
}
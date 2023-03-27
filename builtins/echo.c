#include "../minishell.h"

int ft_echo_n(char *str, t_cmd *cmd)
{
	str = cmd->cmd + 8;
	str = ft_strtrim(str, " ");
	ft_putstr_fd(str, 1);
	return 0;
}

int	ft_echo(t_cmd *cmd)
{
	char *str;

	str = NULL;
	if (ft_strncmp(cmd->cmd, "echo -n ", 8)== 0)
	{
		ft_echo_n(str, cmd);
		return 0;
	}
	else
	{
		str = cmd->cmd + 5;
		str = ft_strtrim(str, " ");
		ft_putendl_fd(str, 1);
		return 0;
	}
	return -1;
}
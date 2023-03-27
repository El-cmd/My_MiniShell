#include "../minishell.h"

int ft_echo_n(t_cmd *cmd)
{
	printf("echo -n : %s" , cmd->cmd + 8);
	return 0;
}

int	ft_echo(t_cmd *cmd)
{
	char *str;

	str = cmd->cmd + 5;
	if (ft_strncmp(str, " -n", 3) == 0)
	{
		ft_echo_n(cmd);
		return 0;
	}
	else
	{
		str = ft_strtrim(str, " ");
		ft_putendl_fd(str, 1);
		return 0;
	}
	return -1;
}
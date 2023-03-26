#include "../minishell.h"

int ft_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		ft_putendl_fd(env[i], 1);
		i++;
	}
	return (0);
}
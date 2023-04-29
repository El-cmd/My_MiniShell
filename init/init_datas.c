#include "../minishell.h"

void	init_data(t_data *data, char **en)
{
	printTitle();
	data->envp = en;
	data->env = init_envp(en);
	signal_handler();
}

void init_data_cmd(t_data *data)
{
	data->cmdIndex = init_cmd();
	data->path_exec = ft_getpath(data->env);
}
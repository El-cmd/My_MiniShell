#include "minishell.h"

void	eternal_loop(t_data *data)
{
	char *str;

	while(1)
	{
		str = readline("MS >> 🤖: ");
		malloc_error(str);
		add_history(str);
		init_data_cmd(data);

		// il faut que je clean a partir d'ici
		splitOrNot(str, data->cmdIndex);
		redirOrNot(data->cmdIndex);
		initRedirOrnot(data->cmdIndex);
		exec(data->cmdIndex, data->path_exec, data->env);

		free(str);
	}
}

int main(int argc, char **argv, char **envp)
{
	t_data data;

	the_arg(argc, argv);
	init_data(&data, envp);
	eternal_loop(&data);
	return (0);
}

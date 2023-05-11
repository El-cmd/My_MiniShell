#include "minishell.h"

//tout est dans le titre de ma fonction
void	eternal_loop(t_data *data)
{
	char *str;

	while(1)
	{
		str = readline("MS#🤖: ");
		add_history(str);
		init_data_cmd(data);

		// il faut que je clean a partir d'ici
		splitOrNot(str, data->cmdIndex);
		//init redirection token
		malloc_all(data);
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

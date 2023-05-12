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
		//t_cmd *tmp = data->cmdIndex->begin;
		//while (tmp)
		//{
		//	printf("just la commande: %s\n", tmp->just_cmd);
		//	printf("just la commande cmd: %s\n", tmp->cmd);
		//	printf("redir: %d\n", tmp->redir);
		//	tmp = tmp->next;
		//}
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
	rl_clear_history();
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:23:57 by vloth             #+#    #+#             */
/*   Updated: 2023/05/22 15:42:48 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
t_global global;
//tout est dans le titre de ma fonction
void	eternal_loop(t_data *data)
{
	char *str;

	while(1)
	{
		str = readline("MS#🤖: ");
		if (!str)
		{
			printf("CTRL-D\nExit\n");
			free(str);
			free_everything(data);
			exit(0);
		}
		add_history(str);
		//init_data_cmd(data, str);
		splitOrNot(str, data->cmdIndex);
		malloc_all(data);
		exec(data);
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

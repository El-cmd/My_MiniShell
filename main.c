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
		add_history(str);
		init_data_cmd(data, str);

		// il faut que je clean a partir d'ici
		splitOrNot(str, data->cmdIndex);
		//init redirection token
		malloc_all(data);
		//printf("%s\n", data->cmdIndex->begin->argv[1]);
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

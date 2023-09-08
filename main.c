/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:23:57 by vloth             #+#    #+#             */
/*   Updated: 2023/09/08 14:50:26 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_global;

void	eternal_loop(t_data *data)
{
	char	*str;

	str = NULL;
	rl_outstream = stderr;
	while (1)
	{
		connect_signal();
		g_global.pid = 0;
		str = readline("MS#🤖: ");
		if (!str)
		{
			printf("Exit\n");
			free(str);
			free_everything(data);
			exit(0);
		}
		add_history(str);
		if (!split_or_not(str, data->cmd_index))
		{
			if (!malloc_all(data))
				exec(data);
		}
		else
			free_list_second(data);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (!isatty(STDIN_FILENO))
		return (EXIT_FAILURE);
	if (envp == NULL || *envp == NULL)
	{
		ft_putstr_fd(ERROR_ENV, 2);
		return (EXIT_FAILURE);
	}
	the_arg(argc, argv);
	init_data(&data, envp);
	eternal_loop(&data);
	rl_clear_history();
	return (0);
}

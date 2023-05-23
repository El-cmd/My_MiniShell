/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:23:57 by vloth             #+#    #+#             */
/*   Updated: 2023/05/23 06:25:23 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
t_global global;

/* this is for debug */
void	print_cmd(t_data *data)
{
	t_cmd	*cmd = data->cmdIndex->begin;
	int		i;

	while (cmd)
	{
		printf("\tcmd:'%s'\tjust_cmd:'%s'\n", cmd->cmd, cmd->just_cmd);
		i = -1;
		while (cmd->argv[++i])
			printf("\targv[%d]: '%s'\n", i, cmd->argv[i]);
		cmd = cmd->next;
	}
}
/*********************/

//tout est dans le titre de ma fonction
void	eternal_loop(t_data *data)
{
	char *str;

	while(1)
	{
		str = readline("MS#🤖: ");
		add_history(str);
		
		/* debug */
		printf("str: '%s'\n", str);
		/********/

		/* I suggest to ft_split the string 'str' in here 'init_data_cmd' 
		** segfault most likely occurs because of the acdessing data which dont exist yet */
		init_data_cmd(data);

		/* debug */
		print_cmd(data);
		/********/
		// il faut que je clean a partir d'ici
		splitOrNot(str, data->cmdIndex);
		//init redirection token
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

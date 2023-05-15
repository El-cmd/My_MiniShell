/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_datas.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:25:14 by vloth             #+#    #+#             */
/*   Updated: 2023/05/15 21:37:59 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
void	init_data(t_data *data, char **en);
void 	init_data_cmd(t_data *data);
*/
//init les datas avant le lancement du shell
void	init_data(t_data *data, char **en)
{
	printTitle();
	data->envp = en;
	data->env = init_envp(en);
	global.pid = 42;
	signal_handler();
}

//init les datas dans la boucle
void init_data_cmd(t_data *data)
{
	data->cmdIndex = init_cmd();
	data->path_exec = ft_getpath(data->env);
}
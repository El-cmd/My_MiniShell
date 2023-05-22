/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:26:28 by vloth             #+#    #+#             */
/*   Updated: 2023/05/22 15:27:57 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//execute la cmd export en affichant notre liste chainee mais pas
//dans lordre alpha, a faire
//ou rajoute une variable dans notre env
int ft_export(t_envSom *env, t_cmd *cmd, t_data *data)
{
	t_env *tmp;

	tmp = env->begin;
	if (cmd->argv[1] == NULL)
	{
		while (tmp)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(tmp->name, 1);
			ft_putchar_fd('\n', 1);
			tmp = tmp->next;
		}
	}
	else
		push_env(cmd->argv[1], env);
	data->exit_return = 0;
	return (0);
}
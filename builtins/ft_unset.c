/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:26:31 by vloth             #+#    #+#             */
/*   Updated: 2023/05/13 18:26:32 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//renvoie la la place du egale dans la cmd
int search_egal(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

//cherche et enleve la variable demandé
int ft_unset(t_envSom *env, t_cmd *cmd, t_data *data)
{
	t_env *tmp;
	char **name;

	tmp = env->begin;
	name = ft_split(cmd->cmd, ' ');
	if (name[1] == NULL)
	{
		data->exit_return = 0;
		return (0);
	}
	while (tmp)
	{
		if (ft_strncmp(tmp->name, name[1], search_egal(tmp->name)) == 0)
		{
			free(tmp->name);
			tmp->name = NULL;
			if (tmp->next == NULL)
			{
				tmp->back->next = NULL;
				return (0);
			}
			tmp->next->back = tmp->back;
			tmp->back->next = tmp->next;
			return (0);
		}
		tmp = tmp->next;
	}
	data->exit_return = 0;
	return (0);
}
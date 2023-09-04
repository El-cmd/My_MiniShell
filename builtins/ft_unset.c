/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:26:31 by vloth             #+#    #+#             */
/*   Updated: 2023/09/03 23:10:44 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//renvoie la la place du egale dans la cmd
int	search_egal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

//cherche et enleve la variable demandée
void	remove_variable(t_env_som *env, t_env *var_to_remove)
{
	if (env == NULL || var_to_remove == NULL)
		return ;
	if (var_to_remove->back == NULL)
	{
		env->begin = var_to_remove->next;
		if (var_to_remove->next != NULL)
			var_to_remove->next->back = NULL;
	}
	else
	{
		if (var_to_remove->next != NULL)
			var_to_remove->next->back = var_to_remove->back;
		var_to_remove->back->next = var_to_remove->next;
	}
	if (var_to_remove == env->end)
		env->end = var_to_remove->back;
	free(var_to_remove->name);
	free(var_to_remove->name_split);
	free(var_to_remove->value_split);
	free(var_to_remove);
	env->size--;
}

int	ft_unset(t_env_som *env, t_cmd *cmd, t_data *data)
{
	int		i;
	int		removed;
	t_env	*tmp;

	i = 1;
	removed = 0;
	while (cmd->argv[i])
	{
		tmp = env->begin;
		while (tmp)
		{
			if (ft_strcmp(cmd->argv[i], tmp->name_split) == 0)
			{
				remove_variable(env, tmp);
				removed = 1;
				break ;
			}
			tmp = tmp->next;
		}
		i++;
	}
	data->exit_return = 1;
	if (removed)
		data->exit_return = 0;
	return (0);
}

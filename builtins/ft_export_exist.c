/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_exist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspeciel <nspeciel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 22:53:19 by nspeciel          #+#    #+#             */
/*   Updated: 2023/09/08 17:07:35 by nspeciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Fonction pour vérifier si une variable existe dans la liste chaînée
int	is_variable_in_list(char *variable, t_env *list)
{
	while (list)
	{
		if (!ft_strcmp(variable, list->name_split))
			return (1);
		list = list->next;
	}
	return (0);
}

// Fonction pour mettre à jour une variable existante dans la liste chaînée
void	update_variable(char **variableParts, t_env *list, char *str)
{
	while (list)
	{
		if (!ft_strcmp(variableParts[0], list->name_split))
		{
			remplace(list, variableParts, str);
			return ;
		}
		list = list->next;
	}
}

// Fonction pour vérifier si une variable existe
int	already_exist(char *str, t_env_som *env)
{
	int		i;
	t_env	*list;
	char	**var;

	i = 0;
	list = env->begin;
	while (str[i])
	{
		if (str[i] == '=')
		{
			var = ft_split(str, '=');
			if (is_variable_in_list(var[0], list))
			{
				update_variable(var, list, str);
				free_tab(var);
				return (1);
			}
			free_tab(var);
		}
		i++;
	}
	if (is_variable_in_list(str, list))
		return (1);
	return (0);
}

int	sign(char *equal, char **name, const char *env_str, char **val)
{
	if (!equal)
	{
		*name = ft_strdup(env_str);
		*val = (char *)malloc(1 * sizeof(char));
		if (!*val)
		{
			printf("Malloc Error\n");
			exit(1);
		}
		(*val)[0] = '\0';
		return (0);
	}
	return (1);
}

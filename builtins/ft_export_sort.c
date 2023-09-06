/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspeciel <nspeciel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 20:51:34 by nspeciel          #+#    #+#             */
/*   Updated: 2023/09/03 22:53:06 by nspeciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Vérifie si une chaîne de caractères existe déjà dans la liste
void	remplace(t_env *tmp2, char **tmp, char *str)
{
	free(tmp2->name_split);
	free(tmp2->value_split);
	tmp2->name_split = strdup(tmp[0]);
	if (tmp[1])
		tmp2->value_split = strdup(tmp[1]);
	tmp2->name = ft_strdup(str);
}

void	alloc_fill(t_env_som *env, char ***env_names, int *env_count)
{
	int		i;
	t_env	*tmp;

	i = 0;
	*env_count = 0;
	tmp = env->begin;
	while (tmp)
	{
		(*env_count)++;
		tmp = tmp->next;
	}
	*env_names = (char **)malloc(*env_count * sizeof(char *));
	if (!(*env_names))
	{
		printf("Erreur d'allocation mémoire.\n");
		exit(1);
	}
	tmp = env->begin;
	i = 0;
	while (tmp)
	{
		(*env_names)[i] = strdup(tmp->name);
		tmp = tmp->next;
		i++;
	}
}

void	bubble_sort(char **arr, int n)
{
	int		swapped;
	int		i;
	char	*temp;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (i < n - 1)
		{
			if (strcmp(arr[i], arr[i + 1]) > 0)
			{
				temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
				swapped = 1;
			}
			i++;
		}
	}
}
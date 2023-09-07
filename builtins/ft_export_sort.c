/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspeciel <nspeciel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 20:51:34 by nspeciel          #+#    #+#             */
/*   Updated: 2023/09/07 12:21:55 by nspeciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Vérifie si une chaîne de caractères existe déjà dans la liste
void	remplace(t_env *tmp2, char **tmp, char *str)
{
	free(tmp2->name_split);
	free(tmp2->value_split);
	free(tmp2->name);
	tmp2->name_split = strdup(tmp[0]);
	if (tmp[1])
		tmp2->value_split = strdup(tmp[1]);
	tmp2->name = ft_strdup(str);
}

void	free_env_names(char **env_names, int env_count)
{
	int	i;

	i = 0;
	while (i < env_count)
	{
		free(env_names[i]);
		i++;
	}
	free(env_names);
}

void	alloc_fill(t_env_som *env, char ***env_names, int *env_count)
{
	int		i;
	t_env	*tmp;
	char	*equal_sign;

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
		(*env_names)[i] = (char *)malloc((strlen(tmp->name) + 3) * sizeof(char));
		if (!(*env_names)[i])
		{
			printf("Erreur d'allocation mémoire.\n");
			exit(1);
		}
		equal_sign = strstr(tmp->name, "=");
		if (equal_sign)
			sprintf((*env_names)[i], "%.*s=\"%s\"", (int)(equal_sign - tmp->name), tmp->name, equal_sign + 1);
		else
			sprintf((*env_names)[i], "%s=\"\"", tmp->name);
		tmp = tmp->next;
		i++;
	}
}

int	ft_export_whithout_arg(t_env_som *env, t_cmd *cmd, t_data *data)
{
	int		env_count;
	char	**env_names;

	if (cmd->argv[1] == NULL)
	{
		alloc_fill(env, &env_names, &env_count);
		bubble_sort(env_names, env_count);
		print_sorted_env(env_names, env_count, data);
		free_env_names(env_names, env_count);
		return (1);
	}
	return (0);
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

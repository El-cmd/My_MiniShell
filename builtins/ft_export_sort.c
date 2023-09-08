/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspeciel <nspeciel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 20:51:34 by nspeciel          #+#    #+#             */
/*   Updated: 2023/09/08 14:00:38 by nspeciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Vérifie si une chaîne de caractères existe déjà dans la liste
void remplace(t_env *tmp2, char **tmp, char *str)
{
    if (tmp2->name_split)
    {
        free(tmp2->name_split);
        tmp2->name_split = NULL;
    }
    if (tmp2->value_split)
    {
        free(tmp2->value_split);
        tmp2->value_split = NULL;
    }
    if (tmp2->name)
    {
        free(tmp2->name);
        tmp2->name = NULL;
    }
    tmp2->name_split = ft_strdup(tmp[0]);
    if (tmp[1])
        tmp2->value_split = ft_strdup(tmp[1]);
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

t_env_som	*create_env_som(void)
{
	t_env_som	*env;

	env = (t_env_som *)malloc(sizeof(t_env_som));
	if (!env)
	{
		printf("Erreur d'allocation mémoire pour t_env_som.\n");
		exit(1);
	}
	env->begin = NULL;
	return (env);
}

void	add_env(t_env_som *env, const char *name)
{
	t_env	*new_env;

	new_env = (t_env *)malloc(sizeof(t_env));
	if (!new_env)
	{
		printf("Erreur d'allocation mémoire pour t_env.\n");
		exit(1);
	}
	new_env->name = ft_strdup(name);
	new_env->next = env->begin;
	env->begin = new_env;
}

char	*format_env_name(const char *name, const char *value)
{
	size_t	result_len;
	char	*result;

	result_len = ft_strlen(name) + ft_strlen(value) + 4;
	result = (char *)malloc((result_len + 1) * sizeof(char));
	if (!result)
	{
		printf("Erreur d'allocation mémoire pour le nom de l'environnement.\n");
		exit(1);
	}
	ft_strlcpy(result, name, result_len + 1);
	ft_strlcat(result, "=\"", result_len + 1);
	ft_strlcat(result, value, result_len + 1);
	ft_strlcat(result, "\"", result_len + 1);
	return (result);
}

// Function to allocate memory for environment names
void	alloc_env_names(char ***env_names, int env_count)
{
	*env_names = (char **)malloc(env_count * sizeof(char *));
	if (!*env_names)
	{
		printf("Erreur d'allocation mémoire pour les noms d'environnement.\n");
		exit(1);
	}
}

// Function to extract name and value from an environment string
void extract_name_and_value(const char *env_str, char **name, char **value)
{
    char *equal_sign;

    equal_sign = ft_strchr(env_str, '=');
    if (!equal_sign)
    {
        *name = ft_strdup(env_str);
        *value = (char *)malloc(1 * sizeof(char)); // Alloue un espace pour une chaîne vide.
        if (!*value)
        {
            printf("Malloc Error\n");
            exit(1);
        }
        (*value)[0] = '\0'; // Place le caractère nul pour créer une chaîne vide.
    }
    else
    {
        *name = (char *)malloc((equal_sign - env_str + 1) * sizeof(char));
        if (!*name)
        {
            printf("Malloc Error\n");
            exit(1);
        }
        ft_strncpy(*name, env_str, equal_sign - env_str);
        (*name)[equal_sign - env_str] = '\0';
        *value = (char *)malloc((ft_strlen(equal_sign + 1) + 1) * sizeof(char));
        if (!*value)
        {
            printf("Malloc Error\n");
            exit(1);
        }
        ft_strcpy(*value, equal_sign + 1);
    }
}


void	alloc_fill(t_env_som *env, char ***env_names, int *env_count)
{
	int		i;
	t_env	*tmp;
	char	*name;
	char	*value;

	i = 0;
	tmp = env->begin;
	*env_count = 0;
	while (tmp)
	{
		(*env_count)++;
		tmp = tmp->next;
	}
	alloc_env_names(env_names, *env_count);
	tmp = env->begin;
	i = 0;
	while (tmp)
	{
		extract_name_and_value(tmp->name, &name, &value);
		(*env_names)[i] = format_env_name(name, value);
		free(name);
		free(value);
		tmp = tmp->next;
		i++;
	}
}

int	ft_export_w_arg(t_env_som *env, t_cmd *cmd, t_data *data)
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
			if (ft_strcmp(arr[i], arr[i + 1]) > 0)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort_second.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:09:19 by vloth             #+#    #+#             */
/*   Updated: 2023/09/08 15:10:25 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remplace(t_env *tmp2, char **tmp, char *str)
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

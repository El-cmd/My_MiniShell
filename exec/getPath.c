/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getPath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:25:51 by vloth             #+#    #+#             */
/*   Updated: 2023/07/10 15:31:04 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//Recup PATH dans mon env et le split avec : pour mon exec
char	**ft_getpath(t_envSom *env)
{
	char	**path;
	t_env	*tmp;

	tmp = env->begin;
	while (tmp && ft_strncmp(tmp->name, "PATH=", 5))
		tmp = tmp->next;
	path = ft_split(tmp->name, ':');
	return (path);
}

int	ft_valid_meta(char *str, t_data *data)
{
	t_env	*tmp;

	tmp = data->env->begin;
	if (str[0] == '?' && str[1] == '\0')
		return (1);
	while (tmp)
	{
		if (!ft_strncmp(tmp->name_split, str, ft_strlen(str)))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

char	*ft_getenv(char *str, t_data *data)
{
	t_env	*tmp;

	tmp = data->env->begin;
	if (str[0] == '?')
		return (ft_itoa(data->exit_return));
	while (tmp)
	{
		if (!ft_strncmp(tmp->name_split, str, ft_strlen(str)))
			return (ft_strdup(tmp->value_split));
		tmp = tmp->next;
	}
	return (NULL);
}

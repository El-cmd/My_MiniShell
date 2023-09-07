/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getPath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:25:51 by vloth             #+#    #+#             */
/*   Updated: 2023/09/07 18:16:08 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//Recup PATH dans mon env et le split avec : pour mon exec
char	**ft_getpath(t_env_som *env)
{
	char	**path;
	t_env	*tmp;

	path = NULL;
	tmp = env->begin;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name_split, "PATH") && tmp->value_split)
		{
			path = ft_split(tmp->value_split, ':');
			break ;
		}
		tmp = tmp->next;
	}
	return (path);
}

int	ft_valid_meta(char *str, t_data *data)
{
	t_env	*tmp;

	tmp = data->env->begin;
	if (str[0] == '?')
		return (1);
	while (tmp)
	{
		if (!ft_strncmp(tmp->name_split, str, (ft_strlen(tmp->name_split))))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

char	*ft_getenv(char *str, t_data *data)
{
	t_env	*tmp;
	char	*tmptmp;
	char	*join;

	tmp = data->env->begin;
	if (str[0] == '?' && str[1])
	{
		tmptmp = ft_itoa(data->exit_return);
		join = ft_strjoin(tmptmp, str + 1);
		free(tmptmp);
		return (join);
	}
	if (str[0] == '?' && str[1] == '\0')
		return (ft_itoa(data->exit_return));
	while (tmp)
	{
		if (!ft_strncmp(tmp->name_split, str, ft_strlen(tmp->name_split)))
			return (ft_strdup(tmp->value_split));
		tmp = tmp->next;
	}
	return (NULL);
}

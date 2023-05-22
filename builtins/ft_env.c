	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:26:25 by vloth             #+#    #+#             */
/*   Updated: 2023/05/13 18:26:26 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


//execute la cmd env en affichant notre liste chainee 
int ft_env(t_envSom *env, t_data *data)
{
	t_env *tmp;

	tmp = env->begin;
	while (tmp)
	{
		ft_putendl_fd(tmp->name, 1);
		tmp = tmp->next;
	}
	data->exit_return = 0; 
	return (0);
}

// regarde si dans notre env il y a la variable oldpwd
int have_olpwd(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "OLDPWD=", 7) == 0)
			return (1);
		i++;
	}
	return (0);
}

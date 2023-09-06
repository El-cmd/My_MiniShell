/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspeciel <nspeciel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:56:32 by nspeciel          #+#    #+#             */
/*   Updated: 2023/08/24 17:31:25 by nspeciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//change la variable pwd dans ma liste de env
void	change_pwd(t_env_som *env)
{	
	t_env	*tmp;
	char	*tmppwd;
	char	**t;

	tmppwd = getcwd(NULL, 0);
	tmp = env->begin;
	while (tmp && ft_strncmp(tmp->name_split, "PWD", 3))
		tmp = tmp->next;
	free(tmp->name);
	tmp->name = ft_strjoin("PWD=", tmppwd);
	t = ft_split(tmp->name, '=');
	free(tmp->name_split);
	tmp->name_split = ft_strdup(t[0]);
	free(tmp->value_split);
	tmp->value_split = ft_strdup(t[1]);
	free_tab(t);
	free(tmppwd);
}

//mes a jours la varible oldpwd dans mon env
void	change_oldpwd(t_env_som *env, char *oldpwd)
{
	t_env	*tmp;
	char	**t;

	tmp = env->begin;
	while (tmp && ft_strncmp(tmp->name_split, "OLDPWD", 6))
		tmp = tmp->next;
	if (tmp)
	{
		free(tmp->name);
		tmp->name = ft_strjoin("OLDPWD=", oldpwd);
		t = ft_split(tmp->name, '=');
		free(tmp->name_split);
		tmp->name_split = ft_strdup(t[0]);
		free(tmp->value_split);
		tmp->value_split = ft_strdup(t[1]);
		free_tab(t);
	}
	else
		push_env(ft_strjoin("OLDPWD=", oldpwd), env);
}
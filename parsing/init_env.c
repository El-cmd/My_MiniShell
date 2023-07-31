/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:25:04 by vloth             #+#    #+#             */
/*   Updated: 2023/07/27 20:00:22 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//init le sommaire de ma double lchainee de env
t_envSom	*init_envSom(void)
{
	t_envSom	*envSom;

	envSom = malloc(sizeof(t_envSom));
	if (!envSom)
		exit(EXIT_FAILURE);
	envSom->begin = NULL;
	envSom->end = NULL;
	envSom->size = 0;
	return (envSom);
}

//pushback les variable denv dans ma liste
void	push_env(char *envp, t_envSom *som)
{
	t_env	*env;
	char	**tmp;

	env = malloc(sizeof(t_env));
	if (!env)
		exit(EXIT_FAILURE);
	env->name = ft_strdup(envp);
	if (have_egal(envp))
	{
		tmp = ft_split(envp, '=');
		env->value_split = ft_strdup(tmp[1]);
		env->name_split = ft_strdup(tmp[0]);
		free_tab(tmp);
	}
	else
		env->name_split = ft_strdup(env->name);
	malloc_error(env->name);
	env->next = NULL;
	env->back = NULL;
	if (som->size == 0)
	{
		som->begin = env;
		som->end = env;
	}
	else
	{
		som->end->next = env;
		env->back = som->end;
		som->end = env;
	}
	som->size++;
}

//change la variable pwd dans ma liste de env
void	change_pwd(t_envSom *env)
{	
	t_env	*tmp;
	char	*tmppwd;

	tmppwd = getcwd(NULL, 0);
	tmp = env->begin;
	while (tmp && ft_strncmp(tmp->name, "PWD=", 4))
		tmp = tmp->next;
	free(tmp->name);
	tmp->name = ft_strjoin("PWD=", tmppwd);
	free(tmppwd);
}

//mes a jours la varible oldpwd dans mon env
void	change_oldpwd(t_envSom *env, char *oldpwd)
{
	t_env	*tmp;

	tmp = env->begin;
	while (tmp && ft_strncmp(tmp->name, "OLDPWD=", 7))
		tmp = tmp->next;
	if (tmp->name)
	{
		free(tmp->name);
		tmp->name = ft_strjoin("OLDPWD=", oldpwd);
	}
	else
		push_env(ft_strjoin("OLDPWD=", oldpwd), env);
}

//mes toute les variable dans ma liste
t_envSom	*init_envp(char **envp)
{
	t_envSom	*env;
	int			i;

	i = 0;
	env = init_envSom();
	while (envp[i])
	{
		push_env(envp[i], env);
		i++;
	}
	change_pwd(env);
	return (env);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldoctor <eldoctor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:25:04 by vloth             #+#    #+#             */
/*   Updated: 2023/08/23 13:07:16 by eldoctor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//init le sommaire de ma double lchainee de env
t_env_som	*init_env_som(void)
{
	t_env_som	*env_som;

	env_som = malloc(sizeof(t_env_som));
	if (!env_som)
		exit(EXIT_FAILURE);
	env_som->begin = NULL;
	env_som->end = NULL;
	env_som->size = 0;
	return (env_som);
}

//pushback les variable denv dans ma liste
t_env	*create_env_node(char *envp)
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
	return (env);
}

void	push_env(char *envp, t_env_som *som)
{
	t_env	*env;

	env = create_env_node(envp);
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

//mes toute les variable dans ma liste
t_env_som	*init_envp(char	**envp)
{
	t_env_som	*env;
	int			i;

	i = 0;
	env = init_env_som();
	while (envp[i])
	{
		push_env(envp[i], env);
		i++;
	}
	change_pwd(env);
	return (env);
}

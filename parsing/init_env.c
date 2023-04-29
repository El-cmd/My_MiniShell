#include "../minishell.h"

t_envSom	*init_envSom(void)
{
	t_envSom *envSom;

	envSom = malloc(sizeof(t_envSom));
	if (!envSom)
		exit(EXIT_FAILURE);
	envSom->begin = NULL;
	envSom->end = NULL;
	envSom->size = 0;
	return (envSom);
}

void	push_env(char *envp, t_envSom *som)
{
	t_env *env;
	
	env = malloc(sizeof(t_env));
    if(!env)
		exit(EXIT_FAILURE);
	env->name = ft_strdup(envp);
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

void	change_pwd(t_envSom *env)
{	
	t_env	*tmp;
	
	tmp = env->begin;
	while (tmp && ft_strncmp(tmp->name, "PWD=", 4))
		tmp = tmp->next;
	tmp->name = ft_strjoin("PWD=", getcwd(NULL, 0));
}

void	change_oldpwd(t_envSom *env, char *oldpwd)
{
	t_env *tmp;

	tmp = env->begin;
	while (tmp && ft_strncmp(tmp->name, "OLDPWD=", 7))
		tmp = tmp->next;
	if (tmp->name)
		tmp->name = ft_strjoin("OLDPWD=", oldpwd);
	else
		push_env(ft_strjoin("OLDPWD=", oldpwd), env);
}

t_envSom	*init_envp(char **envp)
{
	t_envSom *env;
	int i;

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

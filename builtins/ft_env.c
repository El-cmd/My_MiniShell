#include "../minishell.h"

int ft_env(t_envSom *env)
{
	t_env *tmp;

	tmp = env->begin;
	while (tmp)
	{
		ft_putendl_fd(tmp->name, 1);
		tmp = tmp->next;
	}
	return (0);
}

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

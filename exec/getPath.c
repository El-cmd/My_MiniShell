#include "../minishell.h"

char	**ft_getpath(t_envSom *env)
{
	char	*tmpa;
	char	**path;
	t_env 	*tmp;

	tmp = env->begin;
	while (tmp && ft_strncmp(tmp->name, "PATH=", 5))
		tmp = tmp->next;
	tmpa = ft_substr(tmp->name, 5, ft_strlen(tmp->name));
	path = ft_split(tmp->name, ':');
	free(tmpa);
	return (path);
}
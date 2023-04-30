#include "../minishell.h"

//execute la cmd export en affichant notre liste chainee mais pas
//dans lordre alpha, a faire
//ou rajoute une variable dans notre env
int ft_export(t_envSom *env, t_cmd *cmd)
{
	t_env *tmp;
	char **name;

	tmp = env->begin;
	name = ft_split(cmd->cmd, ' ');
	if (name[1] == NULL)
	{
		while (tmp)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(tmp->name, 1);
			ft_putchar_fd('\n', 1);
			tmp = tmp->next;
		}
	}
	else
		push_env(name[1], env);
	return (0);
}
#include "../minishell.h"

int search_egal(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int ft_unset(t_envSom *env, t_cmd *cmd)
{
	t_env *tmp;
	char **name;

	tmp = env->begin;
	name = ft_split(cmd->cmd, ' ');
	if (name[1] == NULL)
		return (0);
	while (tmp)
	{
		if (ft_strncmp(tmp->name, name[1], search_egal(tmp->name)) == 0)
		{
			free(tmp->name);
			tmp->name = NULL;
			if (tmp->next == NULL)
			{
				tmp->back->next = NULL;
				return (0);
			}
			tmp->next->back = tmp->back;
			tmp->back->next = tmp->next;
			return (0);
		}
		tmp = tmp->next;
	};
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:26:28 by vloth             #+#    #+#             */
/*   Updated: 2023/07/31 16:58:41 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int have_egal(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int is_valid(char *str)
{
	int i;

	i = 0;
	if (str[0] == '=' || (str[0] >= '0' && str[0] <= '9'))
	{
		ft_putstr_fd("export: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(" not a valid identifier\n", 2);
		return (0);
	}
	while (str[i])
	{
		if (str[i] == '$' || str[i] == '@' || str[i] == '!' || str[i] == '#'
			|| str[i] == '%' || str[i] == '^' || str[i] == '&' || str[i] == '*')
		{
			ft_putstr_fd("export: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(" not a valid identifier\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

void remplace(t_env *tmp2, char **tmp, char *str)
{
	tmp2->name_split = strdup(tmp[0]);
	if (tmp[1])
		tmp2->value_split = strdup(tmp[1]);
	tmp2->name = ft_strdup(str);
}

int	already_exist(char *str, t_envSom *env)
{
	int i;
	char **tmp;
	t_env *tmp2;
	
	i = 0;
	tmp2 = env->begin;
	while (str[i])
	{
		if (str[i] == '=')
		{
			tmp = ft_split(str, '=');
			while (tmp2)
			{
				if (!ft_strcmp(tmp[0], tmp2->name_split))
				{
					remplace(tmp2, tmp, str);
					free_tab(tmp);
					return (1);
				}
				tmp2 = tmp2->next;
			
			}
			free_tab(tmp);
		}
		i++;
	}
	while (tmp2)
	{
		if (!ft_strcmp(str, tmp2->name_split))
			return (1);
		tmp2 = tmp2->next;
	}
	return (0);
}

int	ft_export(t_envSom *env, t_cmd *cmd, t_data *data)
{
	t_env	*tmp;
	int i;
	int retour;

	i = 1;
	retour = 0;
	tmp = env->begin;
	if (cmd->argv[1] == NULL)
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
	{
		while (cmd->argv[i])
		{		
			if (is_valid(cmd->argv[i]) && !already_exist(cmd->argv[i], env))
				push_env(cmd->argv[i], env);
			else
				retour = 1;
			i++;
		}
	}
	if (retour == 1)
		data->exit_return = 1;
	else
		data->exit_return = 0;
	return (0);
}

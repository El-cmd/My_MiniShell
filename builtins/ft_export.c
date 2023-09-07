/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspeciel <nspeciel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:26:28 by vloth             #+#    #+#             */
/*   Updated: 2023/09/07 10:48:58 by nspeciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_sorted_env(char **env_names, int env_count, t_data *data)
{
	int	i;

	i = 0;
	while (i < env_count)
	{
		printf("declare -x %s\n", env_names[i]);
		i++;
	}
	data->exit_return = 0;
}

int	have_egal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	is_valid(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '=' || (str[0] >= '0' && str[0] <= '9') || str[0] == '$'
		|| strchr(str, '=') == NULL)
	{
		return (0);
	}
	while (str[i])
	{
		if (str[i] == '@' || str[i] == '!' || str[i] == '#'
			|| str[i] == '%' || str[i] == '^' || str[i] == '&' || str[i] == '*')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int ft_export(t_env_som *env, t_cmd *cmd, t_data *data)
{
    int i;
    int retour;

    i = 1;
    retour = 0;
    if (!ft_export_whithout_arg(env, cmd, data))
    {
        while (cmd->argv[i])
        {       
            if (is_valid(cmd->argv[i]))
            {
                if (!already_exist(cmd->argv[i], env))
                    push_env(cmd->argv[i], env);
            }
            else
            {
                retour = 1;
                printf("bash: export: %s: not a valid identifier\n", cmd->argv[i]);
            }
            i++;
        }
    }
    if (retour == 1)
        data->exit_return = 1;
    else
        data->exit_return = 0;
    return (0);
}

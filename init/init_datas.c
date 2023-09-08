/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_datas.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:25:14 by vloth             #+#    #+#             */
/*   Updated: 2023/09/08 18:42:24 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_double_quote(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '"')
			count++;
		i++;
	}
	if (count % 2 != 0)
	{
		ft_putstr_fd("Error: quote\n", 2);
		return (1);
	}
	return (0);
}

int	count_simple_quote(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			count++;
		i++;
	}
	if (count % 2 != 0)
	{
		ft_putstr_fd("Error: quote\n", 2);
		return (1);
	}
	return (0);
}

void	init_data(t_data *data, char **en)
{
	print_title();
	data->exit_return = 0;
	data->envp = en;
	data->env = init_envp(en);
	g_pid = 42;
	data->cmd_index = init_cmd();
	data->path_exec = ft_getpath(data->env);
}

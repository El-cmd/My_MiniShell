/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_datas.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:25:14 by vloth             #+#    #+#             */
/*   Updated: 2023/07/10 15:37:07 by vloth            ###   ########.fr       */
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
	printTitle();
	data->envp = en;
	data->env = init_envp(en);
	global.pid = 42;
	signal_handler();
	data->cmdIndex = init_cmd();
	data->path_exec = ft_getpath(data->env);
}

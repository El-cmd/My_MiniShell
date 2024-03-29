/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspeciel <nspeciel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:26:22 by vloth             #+#    #+#             */
/*   Updated: 2023/09/08 17:08:49 by nspeciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Gestion de l'exit
bool	is_numeric(const char *str)
{
	bool	has_digits;

	if (str == NULL || *str == '\0')
		return (false);
	if (*str == '+' || *str == '-')
		str++;
	has_digits = false;
	while (*str)
	{
		if (!isdigit(*str))
			return (false);
		has_digits = true;
		str++;
	}
	return (has_digits);
}

void	ft_exit(t_cmd *cmd, t_data *data)
{
	const char	*arg;

	printf("exit\n");
	arg = cmd->cmd + 4;
	while (*arg && (*arg == ' ' || *arg == '\t'))
		arg++;
	if (*arg)
	{
		if ((*arg == '\"' || *arg == '\'') && arg[strlen(arg) - 1] == *arg)
		{
			arg++;
		}
		if (!is_numeric(arg))
		{
			printf("MS#🤖: %s: numeric argument required\n", arg);
			free_everything(data);
			exit(2);
		}
		errno = atoi(arg);
		free_everything(data);
		exit(errno);
	}
	free_everything(data);
	exit(0);
}

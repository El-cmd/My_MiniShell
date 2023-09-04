/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_second.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspeciel <nspeciel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 02:22:30 by vloth             #+#    #+#             */
/*   Updated: 2023/09/04 03:03:00 by nspeciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo_quote(t_cmd *cmd)
{
	if (cmd->quotes && !cmd->have_meta && !cmd->redir)
	{
		if (!ft_strncmp(cmd->cmd + 5, "-n", 2)
			&& !ft_strcmp(cmd->argv[0], "echo"))
		{
			ft_echo_text(cmd->cmd + 7);
			return (1);
		}
		else if (!ft_strncmp(cmd->cmd, "echo", 4)
			&& ft_strcmp(cmd->argv[1], "-n")
			&& !ft_strcmp(cmd->argv[0], "echo"))
		{
			ft_echo_text(cmd->cmd + 4);
			write(1, "\n", 1);
			return (1);
		}
	}
	return (0);
}

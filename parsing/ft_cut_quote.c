/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspeciel <nspeciel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 22:57:36 by nspeciel          #+#    #+#             */
/*   Updated: 2023/09/04 02:00:41 by nspeciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_quotes(char **arg)
{
	int		len;
	int		i;
	int		j;
	int		inquotes;
	char	*tmp;

	tmp = strdup(*arg);
	len = strlen(tmp);
	i = 0;
	j = 0;
	inquotes = 0;
	while (i < len)
	{
		if (tmp[i] == '\'' || tmp[i] == '"')
		{
			inquotes = 1 - inquotes;
			i++;
		}
		else
			tmp[j++] = tmp[i++];
	}
	tmp[j] = '\0';
	free(*arg);
	*arg = strdup(tmp);
	free(tmp);
}

void	cut_quote(t_data *data)
{
	int		i;
	t_cmd	*cmd;

	cmd = data->cmd_index->begin;
	while (cmd)
	{
		if (cmd->quotes)
		{
			i = 0;
			while (cmd->argv[i] != NULL)
			{
				process_quotes(&(cmd->argv[i]));
				i++;
			}
		}
		cmd = cmd->next;
	}
}

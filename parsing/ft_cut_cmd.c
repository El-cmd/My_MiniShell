/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:24:57 by vloth             #+#    #+#             */
/*   Updated: 2023/07/10 15:58:57 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parseur_quotes(char *str, int i, int c)
{
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_pipeError(char *line)
{
	int	i;
	int	j;
	int	q;

	i = 0;
	j = 0;
	q = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			i = parseur_quotes(line, i + 1, line[i]);
			if (i == -1)
				return (3);
			q++;
		}
		if (line[i] == '|')
		{
			if (line[i + 1] == '|')
				return (1);
			if (line[i + 1] == '\0')
				return (1);
			j++;
		}
		i++;
	}
	if (j > 0 && q == 0)
		return (0);
	if ((q > 0))
		return (3);
	return (2);
}

void	splitage(char *line, t_cmdIndex *cmdIndex)
{
	char	**line_second;
	char	*tmp;
	int		i;

	i = 0;
	line_second = ft_split(line, '|');
	i = 0;
	while (line_second[i])
	{
		tmp = ft_strtrim(line_second[i], " ");
		pushback_cmd(tmp, cmdIndex, 0);
		free(tmp);
		i++;
	}
	free_tab(line_second);
}

// par rapport a la commande regarde sil doit split ou pas
int	splitOrNot(char *line, t_cmdIndex *cmdIndex)
{
	if (no_str(line) == 1)
		return (1);
	if (ft_pipeError(line) == 1)
		return (1);
	else if (ft_pipeError(line) == 3)
	{
		if (!split_quotes(line, cmdIndex))
			return (1);
		return (0);
	}
	else if (ft_pipeError(line) == 2)
	{
		line = ft_strtrim(line, " ");
		pushback_cmd(line, cmdIndex, 0);
		free(line);
		return (0);
	}
	else if (ft_pipeError(line) == 0)
		splitage(line, cmdIndex);
	return (0);
}

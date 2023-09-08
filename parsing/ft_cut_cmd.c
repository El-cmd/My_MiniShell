/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:24:57 by vloth             #+#    #+#             */
/*   Updated: 2023/09/08 15:59:45 by vloth            ###   ########.fr       */
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

int	check_quotes(char *line)
{
	int	i;
	int	q;

	i = 0;
	q = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			i = parseur_quotes(line, i + 1, line[i]);
			if (i == -1)
				return (-1);
			q++;
		}
		i++;
	}
	return (q);
}

int	check_separators(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			i = parseur_quotes(line, i + 1, line[i]);
			if (i == -1)
			{
				ft_putstr_fd("Quote Error\n", 2);
				return (-1);
			}
		}
		if (line[i] == '|')
		{
			if (line[i + 1] == '|' || line[i + 1] == '\0')
				return (-1);
			j++;
		}
		i++;
	}
	return (j);
}

int	check_error(char *line)
{
	int	j;
	int	q;

	j = check_separators(line);
	q = check_quotes(line);
	if (j == -1 || q == -1)
	{
		ft_putstr_fd("Error: Invalid command\n", 2);
		return (-1);
	}
	return (0);
}

// par rapport a la commande regarde sil doit split ou pas
int	split_or_not(char *line, t_cmd_index *cmd_index)
{
	int		perror;

	perror = error(line);
	if (perror == -1)
		return (1);
	if (check_separators(line) == 0)
		not_pipe(line, cmd_index);
	else
	{
		if (pipe_cut(line, cmd_index))
			return (1);
	}
	free(line);
	return (0);
}

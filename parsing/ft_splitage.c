/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldoctor <eldoctor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:48:10 by nspeciel          #+#    #+#             */
/*   Updated: 2023/09/06 14:52:33 by eldoctor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cmd_vide(char **line)
{
	int	i;
	int	j;
	int	g;

	i = 0;
	j = 0;
	g = 0;
	while (line[i])
	{
		while (line[i][j])
		{
			if (line[i][j] != ' ' && line[i][j] != '|')
				g = 1;
			else if (line[i][j] == ' ')
				while (line[i][j] == ' ')
					j++;
			if ((line[i][j] == '|' || line[i][j] == '\0') && g != 1)
				return (1);
			j++;
		}
		i++;
		j = 0;
		g = 0;
	}
	return (0);
}

int	splitage(char *line, t_cmd_index *cmd_index)
{
	char	**line_second;
	char	*tmp;
	int		i;

	i = 0;
	line_second = ft_split_s(line, '|');
	i = 0;
	if (cmd_vide(line_second))
	{
		ft_putstr_fd("Error: commande vide\n", 2);
		return (1);
	}
	while (line_second[i])
	{
		tmp = ft_strtrim(line_second[i], " ");
		pushback_cmd(tmp, cmd_index, check_quotes(line_second[i]));
		free(tmp);
		i++;
	}
	free_tab(line_second);
	return (0);
}
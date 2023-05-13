/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:24:57 by vloth             #+#    #+#             */
/*   Updated: 2023/05/13 18:33:00 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
int		ft_pipeError(char *line);
void	splitage(char *line, t_cmdIndex *cmdIndex);
void	splitOrNot(char *line, t_cmdIndex *cmdIndex);
*/
// regarde sil y a des pipe ou non
//et aussi si il y a des || ou des pipe invalide genre 
// ls | grep truc | \0
int	ft_pipeError(char *line)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (line[i])
	{
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
	if (j > 0)
		return (0);
	return (2);
}


//split le buffer par rapport au pipe et enleve les espace
//au debut et a la fin de chaque commande
//et enfin les ajoute dans la liste chainé
void	splitage(char *line, t_cmdIndex *cmdIndex)
{
	char	**line_second;
	int i;

	i = 0;
	//toujours ne pas oublier les leaks et d'opti split
	line_second = ft_split(line, '|');
	while (line_second[i])
	{
		line_second[i] = ft_strtrim(line_second[i], " ");
		i++;
	}
	i = 0;
	while (line_second[i])
	{
		pushback_cmd(line_second[i], cmdIndex);
		i++;
	}
}

// par rapport a la commande regarde sil doit split ou pas
void	splitOrNot(char *line, t_cmdIndex *cmdIndex)
{
	if (ft_pipeError(line) == 1)
		return ;
	else if (ft_pipeError(line) == 2)
	{
		line = ft_strtrim(line, " ");
		pushback_cmd(line, cmdIndex);
	}
	else if (ft_pipeError(line) == 0)
		splitage(line, cmdIndex);
}

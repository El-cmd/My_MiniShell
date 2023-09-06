/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspeciel <nspeciel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:48:10 by nspeciel          #+#    #+#             */
/*   Updated: 2023/09/06 20:23:14 by nspeciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int cmd_vide(char **line)
{
    int i;
    int j;
    bool separator; // Utilisation d'un indicateur booléen pour plus de clarté

    i = 0;
    while (line[i])
	{
        j = 0;
        separator = false; // Initialisation de l'indicateur à faux pour chaque nouvelle chaîne
        while (line[i][j])
		{
            if (line[i][j] != ' ' && line[i][j] != '|')
			{
                separator = true; // Définir l'indicateur à vrai si un caractère autre que ' ' ou '|' est trouvé
                break; // Sortir de la boucle interne dès qu'un caractère est trouvé
            }
            j++;
        }
        if (!separator)
		{
			return 1;
		}
        i++;
    }
    return 0;
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

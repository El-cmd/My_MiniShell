/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldoctor <eldoctor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:24:57 by vloth             #+#    #+#             */
/*   Updated: 2023/09/06 02:24:31 by eldoctor         ###   ########.fr       */
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
				ft_putstr_fd("Pipe Error", 2);
				return (-1);
			}
		}
		
		if (line[i] == '|')
		{
			if (line[i + 1] == '|')
				return (-1);
			if (line[i + 1] == '\0')
				return (-1);
			j++;
		}
		i++;
	}
	return (j);
}

int	ft_pipe_error(char *line)
{
	int	j;
	int	q;

	j = check_separators(line);
	q = check_quotes(line);
	if (j == -1)
	{
		ft_putstr_fd("Error: Invalid command\n", 2);
		return (-1);
	}
	if (j > 0 && q == 0)
		return (0);
	if (q > 0)
		return (3);
	return (2);
}

// par rapport a la commande regarde sil doit split ou pas
int	split_or_not(char *line, t_cmd_index *cmd_index)
{
	int		pipe_error;

	pipe_error = error(line);
	if (pipe_error == -1)
		return (1);
	else if (pipe_error == 3)
	{
		//if (pipe_quote(line, cmd_index))
		char **test = ft_split_s(line, '|'); //si tu veux le refaire fonctionner comment avant
		int i = 0;							//Commente cette condition et remet celle
		while (test[i])						//la en commentaire 
		{									// jai fini mon split qui split un pipe ou		
			printf("%s\n", test[i]);		// ou des espace sans toucher a ce quil y a entre
			i++;
		}
			return (1);
	}
	else if (pipe_error == 2)
		not_pipe(line, cmd_index);
	else if (pipe_error == 0)
	{
		if (pipe_cut(line, cmd_index))
			return (1);
	}
	free(line);
	return (0);
}

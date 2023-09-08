/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 23:14:20 by vloth             #+#    #+#             */
/*   Updated: 2023/09/08 17:38:50 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	p_q(char *s1, int i)
{
	if (s1[i] == '"' || s1[i] == '\'')
	{
		i = parseur_quotes(s1, i + 1, s1[i]);
		if (i == -1)
		{
			ft_putstr_fd("Pipe Error\n", 2);
			return (-1);
		}
	}
	return (i);
}

int	special_quotes_ss(char *str, int i, char *s2, int *k)
{
	int	u;

	u = 1;
	while (str[i])
	{
		if (u == 1)
		{
			u = 0;
			s2[*k] = str[i - 1];
			*k = *k + 1;
		}
		if (str[i] == '\'')
			return (i);
		s2[*k] = str[i];
		*k = *k + 1;
		i++;
	}
	return (-1);
}

int	special_quotes_d(char *str, int i, char *s2, int *k)
{
	int	u;

	u = 1;
	while (str[i])
	{
		if (u == 1)
		{
			u = 0;
			s2[*k] = str[i - 1];
			*k = *k + 1;
		}
		if (str[i] == '\"')
			return (i);
		s2[*k] = str[i];
		*k = *k + 1;
		i++;
	}
	return (-1);
}

void	split_norm(char *s, char *dst, int *k, int *i)
{
	if (s[*i] == '\'')
	{
		dst[*k] = s[*i];
		*i = special_quotes_ss(s, *i + 1, dst, k);
	}
	else if (s[*i] == '\"')
	{
		dst[*k] = s[*i];
		*i = special_quotes_d(s, *i + 1, dst, k);
	}
}

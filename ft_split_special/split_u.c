/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <vloth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 18:13:09 by vloth             #+#    #+#             */
/*   Updated: 2023/09/08 18:22:49 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	split_norm_second(char *s, char *dst, int *k, int *i)
{
		dst[*k] = s[*i];
		*i = special_quotes_ss(s, *i + 1, dst, k);
}

int	pqq(char *s1, int *i)
{
	*i = parseur_quotes(s1, *i + 1, s1[*i]);
	if (*i == -1)
	{
		ft_putstr_fd("Pipe Error\n", 2);
		return (-1);
	}
	return (0);
}

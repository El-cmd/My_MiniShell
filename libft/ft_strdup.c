/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 10:55:42 by vloth             #+#    #+#             */
/*   Updated: 2021/06/17 10:33:12 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../minishell.h"

char	*ft_strdup(const char *s)
{
	char	*tab;
	size_t	n;

	n = 0;
	tab = malloc(sizeof (char) * ft_strlen(s) + 1);
	malloc_error(tab);
	while (s[n])
	{
		tab[n] = s[n];
		n++;
	}
	tab[n] = 0;
	return (tab);
}

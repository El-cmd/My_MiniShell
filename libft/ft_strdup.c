/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspeciel <nspeciel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 10:55:42 by vloth             #+#    #+#             */
/*   Updated: 2023/09/08 13:42:40 by nspeciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../minishell.h"

char	*ft_strdup(const char *s)
{
	char	*tab;
	size_t	n;
	int		error;

	n = 0;
	error = ft_strlen(s);
	if (error == 0)
		return ('\0');
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

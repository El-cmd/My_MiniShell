/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 16:46:25 by vloth             #+#    #+#             */
/*   Updated: 2021/06/17 10:33:44 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	n;
	int	j;

	j = 0;
	i = 0;
	n = 1;
	while (nptr[i] == '\t' || nptr[i] == '\n' || nptr[i] == '\f'
		|| nptr[i] == '\r' || nptr[i] == '\v' || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			n *= -1;
		i++;
	}
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		j = j * 10 + (nptr[i] - 48);
		i++;
	}
	return (n * j);
}

int    ft_atoi_exit(const char *nptr)
{
    int    i;
    int    n;
    int    j;

    j = 0;
    i = 0;
    n = 1;
    while (nptr[i] == '\t' || nptr[i] == '\n' || nptr[i] == '\f'
        || nptr[i] == '\r' || nptr[i] == '\v' || nptr[i] == ' ')
        i++;
    if (nptr[i] != '-' && nptr[i] != '+' && (nptr[i] < 48 || nptr[i] > 57))
        return (2);
    if (nptr[i] == '-' || nptr[i] == '+')
    {
        if (nptr[i] == '-')
            n *= -1;
        i++;
    }
    while (nptr[i] >= 48 && nptr[i] <= 57)
    {
        j = j * 10 + (nptr[i] - 48);
        i++;
    }
    return (n * j);
}
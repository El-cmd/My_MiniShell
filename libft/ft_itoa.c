/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 16:22:39 by vloth             #+#    #+#             */
/*   Updated: 2021/06/15 15:31:50 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long int	static	ft_isneg(long int n)
{
	if (n < 0)
		return (n * (-1));
	return (n);
}

int static 	ft_len(long int n)
{
	int	len;

	len = 0;
	if (n < 0)
		len++;
	if (n == 0)
		len = 1;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{	
	int			i;
	int			len;
	char		*itoa;
	int			res;
	long int	w;

	w = n;
	res = 0;
	i = 0;
	len = ft_len(w);
	itoa = malloc(sizeof(char) * (len + 1));
	if (!itoa)
		return (0);
	while (i < len)
	{	
		w = ft_isneg(w);
		res = w % 10;
		w = w / 10;
		itoa[len - (i + 1)] = res + 48;
		i++;
	}
	if (itoa[0] == 48 && len != 1)
		itoa[0] = '-';
	itoa[len] = 0;
	return (itoa);
}

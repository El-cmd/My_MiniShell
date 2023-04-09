/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 15:58:04 by vloth             #+#    #+#             */
/*   Updated: 2021/06/17 10:31:30 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ns;

	ns = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (ns[i] == (unsigned char)c)
			return (&ns[i]);
		i++;
	}
	return (0);
}

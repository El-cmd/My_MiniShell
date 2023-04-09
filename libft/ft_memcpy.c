/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 16:07:53 by vloth             #+#    #+#             */
/*   Updated: 2021/06/16 16:07:45 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*ndest;
	char	*nsrc;
	size_t	i;

	ndest = (char *)dest;
	nsrc = (char *)src;
	if (!dest && !src)
		return (0);
	i = 0;
	while (n > i)
	{
		ndest[i] = nsrc[i];
		i++;
	}
	return (dest);
}

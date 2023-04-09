/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 16:22:32 by vloth             #+#    #+#             */
/*   Updated: 2021/06/16 16:16:34 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	n;
	size_t	w;
	size_t	j;

	j = ft_strlen(src);
	w = 0;
	n = ft_strlen(dest);
	if (size <= n)
		return (size + j);
	while (src[w] && (n + 1) < size)
	{
		dest[n] = src[w];
		w++;
		n++;
	}
	dest[n] = 0;
	return (n + ft_strlen(&src[w]));
}

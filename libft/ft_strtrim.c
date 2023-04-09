/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 19:32:36 by vloth             #+#    #+#             */
/*   Updated: 2021/06/15 16:15:42 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*sbis;
	unsigned int	i;
	int				len;

	sbis = (char *)s1;
	if (!sbis || !set)
		return (NULL);
	i = 0;
	while (sbis[i] && ft_strchr(set, sbis[i]))
		i++;
	len = ft_strlen(sbis + i);
	if (len)
	{
		while (sbis[i + len - 1] != '\0' && ft_strchr(set, sbis[i + len - 1]))
			len--;
	}
	return (ft_substr(sbis, i, len));
}

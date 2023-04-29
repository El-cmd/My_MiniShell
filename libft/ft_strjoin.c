/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 13:31:02 by vloth             #+#    #+#             */
/*   Updated: 2021/06/09 12:07:30 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../minishell.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*join;
	size_t	i;
	size_t	n;

	n = 0;
	i = 0;
	if (!s1 || !s2)
		return (0);
	join = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	malloc_error(join);
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[n])
	{
		join[i] = s2[n];
		i++;
		n++;
	}
	join[i] = 0;
	return (join);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 12:07:05 by vloth             #+#    #+#             */
/*   Updated: 2021/06/16 17:33:07 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	int		i;

	new = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		new = malloc(sizeof(char) * 1);
		malloc_error(new);
		new[0] = '\0';
		return (new);
	}
	if (len > ft_strlen(&s[start]))
		new = malloc(sizeof(char) * ft_strlen(&s[start]) + 1);
	else
		new = malloc(sizeof(char) * len + 1);
	malloc_error(new);
	i = 0;
	while (s[start] != '\0' && len-- != 0)
		new[i++] = s[start++];
	new[i] = '\0';
	return (new);
}

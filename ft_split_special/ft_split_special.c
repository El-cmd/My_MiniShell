/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_special.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspeciel <nspeciel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 21:54:01 by eldoctor          #+#    #+#             */
/*   Updated: 2023/09/07 12:26:10 by nspeciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	numstring_special(char *s1, char c)
{
	int	comp;
	int	cles;
	int	i;

	comp = 0;
	i = 0;
	cles = 0;
	if (*s1 == '\0')
		return (0);
	while (s1[i] != '\0')
	{
		if (s1[i] == '"' || s1[i] == '\'')
		{
			i = parseur_quotes(s1, i + 1, s1[i]);
			if (i == -1)
			{
				ft_putstr_fd("Pipe Error\n", 2);
				return (-1);
			}
		}
		if (s1[i] == c)
			cles = 0;
		else if (cles == 0)
		{
			cles = 1;
			comp++;
		}
		i++;
	}
	return (comp);
}

int	parseur_quotes_special(char *str, int i, int c, int *length)
{
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
		(*length)++;
	}
	return (-1);
}

static int	numchar_special(char *s2, char c, int i)
{
	int	lenght;

	lenght = 0;
	while (s2[i] != c && s2[i] != '\0')
	{
		if (s2[i] == '"' || s2[i] == '\'')
			i = parseur_quotes_special(s2, i + 1, s2[i], &lenght);
		lenght++;
		i++;
	}
	return (lenght);
}

int	special_quotes(char *str, int i, int c, char *s2, int *k)
{
	int	u;

	u = 1;
	while (str[i])
	{
		if (u == 1)
		{
			u = 0;
			s2[*k] = str[i - 1];
			*k = *k + 1;
		}
		if (str[i] == c)
			return (i);
		s2[*k] = str[i];
		*k = *k + 1;
		i++;
	}
	return (-1);
}

static char	**affect_special(char *s, char **dst, char c, int l)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (s[i] != '\0' && j < l)
	{
		k = 0;
		while (s[i] == c)
			i++;
		dst[j] = (char *)malloc(sizeof(char) * (numchar_special(s, c, i) + 3));
		if (dst[j] == NULL)
			return (freee(dst, j));
		while (s[i] != '\0' && s[i] != c)
		{
			if (s[i] == '\'' || s[i] == '\"')
			{
				dst[j][k] = s[i];
				i = special_quotes(s, i + 1, s[i], dst[j], &k);
			}
			dst[j][k++] = s[i++];
		}
		dst[j][k] = '\0';
		j++;
	}
	dst[j] = NULL;
	return (dst);
}

char	**ft_split_s(char *s, char c)
{
	char	**dst;
	int		l;

	if (s == NULL)
		return (NULL);
	l = numstring_special(s, c);
	dst = (char **)malloc(sizeof(char *) * (l + 1));
	if (dst == NULL)
		return (NULL);
	dst = affect_special(s, dst, c, l);
	if (dst == NULL)
	{
		free(dst);
		return (NULL);
	}
	return (dst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 13:30:44 by vloth             #+#    #+#             */
/*   Updated: 2021/06/12 13:56:40 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*nelement;

	nelement = malloc(sizeof(*nelement));
	if (!nelement)
		return (0);
	nelement->content = content;
	nelement->next = NULL;
	return (nelement);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 13:24:37 by vloth             #+#    #+#             */
/*   Updated: 2021/06/17 12:53:40 by vloth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*n_list;
	t_list	*tmp;

	if (!lst || !f)
		return (0);
	n_list = ft_lstnew((*f)(lst->content));
	if (!n_list)
		return (0);
	lst = lst->next;
	while (lst)
	{
		tmp = ft_lstnew((*f)(lst->content));
		if (!tmp)
		{
			ft_lstclear(&n_list, del);
			return (0);
		}
		ft_lstadd_back(&n_list, tmp);
		lst = lst->next;
	}
	return (n_list);
}

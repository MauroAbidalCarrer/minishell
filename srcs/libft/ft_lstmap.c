/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:35:07 by maabidal          #+#    #+#             */
/*   Updated: 2021/12/14 19:05:03 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_front;
	t_list	*node;

	new_front = NULL;
	while (lst)
	{
		node = ft_lstnew((*f)(lst->content));
		if (node == NULL)
		{
			ft_lstclear(&new_front, del);
			break ;
		}
		ft_lstadd_back(&new_front, node);
		lst = lst->next;
	}
	return (new_front);
}

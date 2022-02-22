/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:21:42 by maabidal          #+#    #+#             */
/*   Updated: 2021/12/14 19:04:27 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	rec_del(t_list *n, void (*del)(void *))
{
	if (!n)
		return ;
	(*del)(n->content);
	rec_del(n->next, del);
	free(n);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	if (lst == NULL)
		return ;
	rec_del(*lst, del);
	*lst = NULL;
}

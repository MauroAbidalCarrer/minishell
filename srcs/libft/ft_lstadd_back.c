/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:16:14 by maabidal          #+#    #+#             */
/*   Updated: 2021/12/14 19:04:02 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*last;

	if (alst == NULL)
		return ;
	last = ft_lstlast(*alst);
	if (last == NULL)
		*alst = new;
	else
		last->next = new;
}

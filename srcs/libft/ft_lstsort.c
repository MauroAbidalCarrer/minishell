/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 17:19:37 by jmaia             #+#    #+#             */
/*   Updated: 2022/03/11 15:35:00 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	swap(void **v1, void **v2);

void	ft_lstsort(t_list *lst, int (*cmp)(void *, void *))
{
	t_list	*cur1;
	t_list	*cur2;

	cur1 = lst;
	while (cur1->next)
	{
		cur2 = cur1->next;
		while (cur2)
		{
			if (cmp(cur1->content, cur2->content) > 0)
				swap(&cur1->content, &cur2->content);
			cur2 = cur2->next;
		}
		cur1 = cur1->next;
	}
}

static void	swap(void **v1, void **v2)
{
	void	*tmp;

	tmp = *v1;
	*v1 = *v2;
	*v2 = tmp;
}

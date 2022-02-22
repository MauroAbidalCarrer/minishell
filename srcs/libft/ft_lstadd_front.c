/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:02:01 by maabidal          #+#    #+#             */
/*   Updated: 2021/12/14 15:07:50 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_lstadd_front(t_list **alst, t_list *new)
{
	if (alst != NULL)
	{
		if (new != NULL)
			new->next = *alst;
		*alst = new;
	}
}

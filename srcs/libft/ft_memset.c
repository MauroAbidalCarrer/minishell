/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 19:44:47 by maabidal          #+#    #+#             */
/*   Updated: 2021/12/13 19:45:04 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned long	i;
	char			*ptr;

	ptr = (char *)b;
	i = 0;
	while (i < len)
		ptr[i++] = (char)c;
	return (ptr);
}

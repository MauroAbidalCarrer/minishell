/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 19:45:52 by maabidal          #+#    #+#             */
/*   Updated: 2021/12/16 15:58:11 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*i1;
	unsigned char	*i2;

	i1 = (unsigned char *)src;
	i2 = (unsigned char *)dest;
	if (i1 == NULL && i2 == NULL)
		return (NULL);
	while (n > 0)
	{
		*i2 = *i1;
		i1++;
		i2++;
		n--;
	}
	return (dest);
}

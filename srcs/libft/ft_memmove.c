/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 19:46:26 by maabidal          #+#    #+#             */
/*   Updated: 2021/12/16 15:58:31 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned int	i;
	unsigned char	*d;
	unsigned char	*s;

	s = (unsigned char *)src;
	d = (unsigned char *)dest;
	if (!s || !d)
		return (NULL);
	if (s < d)
	{
		while (n > 0)
		{
			n--;
			d[n] = s[n];
		}
		return (d);
	}
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}

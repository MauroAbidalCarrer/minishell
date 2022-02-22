/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 20:06:31 by maabidal          #+#    #+#             */
/*   Updated: 2021/12/03 21:16:14 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_strlcpy(char *dst, const char *src, size_t size)
{
	int			n;
	char		*d;
	const char	*s;

	d = dst;
	s = src;
	n = size;
	if (n != 0)
	{
		while (--n != 0)
		{
			*d++ = *s++;
			if (d[-1] == '\0')
				break ;
		}
	}
	if (n == 0)
	{
		if (size != 0)
			*d = '\0';
		while (*s++)
			;
	}
	return (s - src - 1);
}

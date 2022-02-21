/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 18:30:41 by maabidal          #+#    #+#             */
/*   Updated: 2021/12/03 21:20:35 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	if (size == 0)
		return (size + ft_strlen(src));
	i = 0;
	while (dst[i])
	{
		if (i + 1 == size)
			return (size + ft_strlen(src));
		i++;
	}
	j = 0;
	while (src[j] && i + j < size - 1)
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = 0;
	return (i + ft_strlen(src));
}
/*
#include<stdio.h>
#include<string.h>
int main()
{
	char dst[4] = "";
	char src[] = "the cake is a lie !\0I'm hidden lol\r\n";
	int len = strlen(dst) + strlen(src);
	int i = ft_strlcat(dst, "thx to ntoniolo for this test !", 4);
	printf("\nreturned %d\ndstafter=%s\n", i, dst);
}
*/

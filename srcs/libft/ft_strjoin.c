/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 19:27:34 by maabidal          #+#    #+#             */
/*   Updated: 2022/02/22 15:24:25 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		length;

	if (!s1 || !s2)
		return (NULL);
	length = ft_strlen(s1) + ft_strlen(s2) + 1;
	new = ft_malloc(sizeof(char) * length);
	while (*s1)
		*new++ = *s1++;
	while (*s2)
		*new++ = *s2++;
	*new = 0;
	return (new - length + 1);
}

/*
#include<stdio.h>
int main(int ac,char** av)
{
	printf("%s\n", ft_strjoin(av[1], av[2]));
}
*/

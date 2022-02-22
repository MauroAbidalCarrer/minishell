/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 19:40:24 by maabidal          #+#    #+#             */
/*   Updated: 2021/12/13 19:40:42 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	*j;
	char	*s;

	s = (char *)str;
	i = -1;
	j = 0;
	while (s[++i])
	{
		if (s[i] == (char)c)
			j = s + i;
	}
	if (c == 0)
		return (s + i);
	return (j);
}

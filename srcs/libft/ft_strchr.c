/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 19:38:59 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/10 00:24:10 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strchr(const char *str, int c)
{
	char	*s;

	s = (char *)str;
	while (*s && *s != (char)c)
		s++;
	if (*s == (char)c)
		return (s);
	return (0);
}

int	i_strchr(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ilen_strchr(char *str, char c)
{
	if (i_strchr(str, c) != -1)
		return (i_strchr(str, c));
	return (ft_strlen(str));
}

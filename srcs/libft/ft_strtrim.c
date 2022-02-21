/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtrim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 20:56:14 by maabidal          #+#    #+#             */
/*   Updated: 2021/12/03 21:18:03 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*subsub(char const *s, unsigned int start, size_t len)
{
	char	*new;

	if (s == NULL)
		return (NULL);
	if (start + len > ft_strlen(s) || len == 0)
	{
		new = malloc(sizeof(char));
		*new = 0;
		return (new);
	}
	new = malloc((len + 1) * sizeof(char));
	if (new == NULL)
		return (NULL);
	new[len] = 0;
	while (1)
	{
		len--;
		new[len] = s[start + len];
		if (len == 0)
			break ;
	}
	return (new);
}

static int	isin(char c, char const *s)
{
	char	*str;

	str = (char *)s;
	while (*str)
	{
		if (c == *str++)
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	start;
	int	end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && isin(s1[start], set))
		start++;
	end = (int)ft_strlen(s1) - 1;
	while (end > start && isin(s1[end], set))
		end--;
	return (subsub(s1, start, end - start + 1));
}

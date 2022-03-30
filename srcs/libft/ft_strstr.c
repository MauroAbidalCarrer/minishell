/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 19:37:26 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/23 15:43:33 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*dastack;

	if (!haystack || !needle)
		return (0);
	len = ft_strlen(haystack);
	dastack = (char *)haystack;
	if (!*needle)
		return (dastack);
	i = 0;
	while (dastack[i] && i < len)
	{
		j = 0;
		while (dastack[i + j] == needle[j] && i + j < len)
		{
			if (!needle[j + 1])
				return (dastack + i);
			j++;
		}
		i++;
	}
	return (0);
}

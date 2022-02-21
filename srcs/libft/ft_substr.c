/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 17:18:35 by maabidal          #+#    #+#             */
/*   Updated: 2021/12/03 22:56:11 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

static int	min(size_t a, size_t b)
{
	if (a < b)
		return (a);
	return (b);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;

	if (s == NULL)
		return (NULL);
	len = min((size_t)max((int)ft_strlen(s) - start, 0), len);
	new = malloc((len + 1) * sizeof(char));
	if (new == NULL)
		return (NULL);
	new[len] = 0;
	i = 0;
	while (i < len)
	{
		new[i] = s[start + i];
		i++;
	}
	return (new);
}
/*
#include<stdio.h>
int main(int ac, char** av)
{
	char *str = ft_substr(av[1], atoi(av[2]), atoi(av[3]));
	printf("%s\n", str);
	free(str);
}
*/

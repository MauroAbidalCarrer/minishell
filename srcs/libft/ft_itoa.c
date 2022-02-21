/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 22:17:01 by maabidal          #+#    #+#             */
/*   Updated: 2021/12/03 21:14:39 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static long	ft_abs(int n)
{
	long	o;

	o = (long)n;
	if (o < 0)
		return (-o);
	return (o);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	i;

	len = (n < 0) + 1;
	i = ft_abs(n);
	while (i >= 10)
	{
		i /= 10;
		len++;
	}
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	str[len] = 0;
	*str = '-';
	i = ft_abs(n);
	n = (n < 0);
	while (--len >= n)
	{
		str[len] = '0' + i % 10;
		i /= 10;
	}
	return (str);
}
/*
#include<stdio.h>
int main(int ac, char ** av)
{
	for (int i = 1; i < ac; i++)
	{
		char *nb = ft_itoa(atoi(av[i]));
		printf("%s\n", nb);
		free(nb);
	}
}
*/

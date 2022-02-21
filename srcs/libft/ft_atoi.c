/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:24:58 by maabidal          #+#    #+#             */
/*   Updated: 2021/12/03 21:14:23 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	inrange(char c, char a, char b)
{
	return (c >= a && c <= b);
}

static int	iswhite(char c)
{
	return (c == ' ' || inrange(c, 9, 13));
}

int	ft_atoi(const char *nptr)
{
	long	sign;
	long	nb;

	while (iswhite(*nptr))
		nptr++;
	sign = 1 - 2 * (*nptr == '-');
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	nb = 0;
	while (inrange(*nptr, '0', '9'))
		nb = nb * 10 + *nptr++ - '0';
	return ((int)(nb * sign));
}
/*
#include<stdlib.h>
#include<stdio.h>
int test(char* test)
{
	int my = ft_atoi(test);
	int og = atoi(test);
	printf("test= %s\nmy = %d\nog = %d\n\n", test, my, og);
	return (og != my);
}
int main(int ac, char** av)
{
	char tests [][30] =
	{
		"123",
		"",
		"-+-+321",
		"gqwve",
		"-123123123123123123",
		"2147483647",
		"  -2147483648",
		"\t\r\n  -2147483648"
	};
	printf("Testing inputs\n");
	int errors = 0;
	for (int i = 0; i < 8; i++)
		errors += test(tests[i]);
	for (int i = 1; i < ac; i++)
		errors += test(av[i]);
	if (errors == 0)
		printf("No errors encountered.\n");
	else
		printf("Erros ecountered.\n");
}
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:29:25 by maabidal          #+#    #+#             */
/*   Updated: 2021/12/03 21:14:33 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	long			length;
	unsigned char	*add;

	length = (long)nmemb * (long)size;
	if (length >= (long)INT_MAX)
		return (NULL);
	add = malloc(length);
	if (add == NULL)
		return (NULL);
	while (--length >= 0)
		add[length] = 0;
	return ((void *)add);
}
/*
#include<stdio.h>
int test(int nmemb, int size)
{
	unsigned char* my = ft_calloc(nmemb,size);
	unsigned char* og = calloc(nmemb,size);
	if ((my == NULL) != (og == NULL))
	{
		printf("nmemb= %d, size= %d\nmy= %p\nog= %p\n", nmemb, size, my, og);
		return 1;
	}
	int erros = 0;
	for (int i = 0; i < nmemb * size; i++)
	{
		if(my[i] != 0)
		{
			erros++;
			printf("%p = %d\n",  my + i, my[i]);
		}
	}
	free (my);
	free (og);
	return erros;
}
int main()
{
	int tests[][2] = 
	{
		{213, 3},
		{42 ,123},
		{232,0}
	};
	printf("Starting tests.\n");
	int errors = 0;
	for (int i = 0; i < 3; i++)
		errors += test(tests[i][0], tests[i][1]);
	if (errors > 0)
		printf("%d erros encountered.\n",errors);
	else
		printf("No erros encountered.\n");
}
*/

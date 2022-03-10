/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_equal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:51:16 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/08 14:57:02 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	str_equal(char *str1, char *str2)
{
	while (*str1 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return (*str1 == *str2);
}

/*
#include<stdio.h>
int	main(int ac, char **av)
{
printf("str_equal(\"%s\", \"%s\")=%d\n",av[1],av[2],str_equal(av[1],av[2]));
}
*/

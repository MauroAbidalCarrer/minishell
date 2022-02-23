/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_starts_by.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 23:35:48 by maabidal          #+#    #+#             */
/*   Updated: 2022/02/23 12:06:22 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "libft.h"
#include <stdio.h>

//returns str if str dosen't start by str2
//returns str + ft_strlen(str2) otherwise
char	*str_starts_by(char *str, char *str2)
{
	char	*str1;

	str1 = str;
	while (*str1 && *str2 && *str1 == *str2)
	{
		if (str2[1] == 0)
			return (str1 + 1);
		str1++;
		str2++;
	}
	return (str);
}

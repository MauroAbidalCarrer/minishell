/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_starts_by.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 23:35:48 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/16 17:52:41 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "libft.h"
#include <stdio.h>

//returns str if str dosen't start by str2
//returns str + ft_strlen(str2) otherwise
int	starts_by(char **str, char *str2)
{
	char	*str1;

	str1 = *str;
	while (*str1 && *str2 && *str1 == *str2)
	{
		if (str2[1] == 0)
		{
			*str = str1 + 1;
			return (1);
		}
		str1++;
		str2++;
	}
	return (0);
}

/* NEED TO BE DELETED */
/* This function needs to be written */
int	set_env_var(char const *key, char const *value)
{
	(void) key;
	(void) value;
	return (0);
}

/* NEED TO DELETED */
/* This function needs to be written */
int	delete_env_var(char const *key)
{
	(void) key;
	return (0);
}

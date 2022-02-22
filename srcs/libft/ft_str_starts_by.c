/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_starts_by.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 23:35:48 by maabidal          #+#    #+#             */
/*   Updated: 2022/02/22 23:37:03 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//returns str if str dosen't start by str2
//returns str + ft_strlen(str2) otherwise
char	*str_starts_by(char *str, char *str2)
{
	while (*str && *str2 && *str == *str2)
	{
		if (str2[1] == 0)
			return (str + 1);
		str++;
		str2++;
	}
	return (str);
}

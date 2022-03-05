/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnochr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 17:32:37 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/06 00:44:49 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*strnochr(char *str, char c)
{
	if (str == NULL)
		return (NULL);
	while (*str && *str == c)
		str++;
	return (str);
}

char	*skip_spaces(char *str)
{
	while (is_white(*str))
		str++;
	return (str);
}

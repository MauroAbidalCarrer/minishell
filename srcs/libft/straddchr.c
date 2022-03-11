/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   straddchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 04:22:13 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/11 04:22:37 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*straddchar(char *str, char c)
{
	char	*tmp;
	int		len;

	len = ft_strlen(str);
	tmp = ft_malloc(sizeof(char) * (len + 2));
	tmp[len] = c;
	tmp[len + 1] = 0;
	while (--len >= 0)
		tmp[len] = str[len];
	return (tmp);
}

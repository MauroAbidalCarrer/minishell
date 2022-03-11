/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 08:46:59 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/11 10:48:43 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"

char	*strstr_qp(char *str, char *needle)
{
	char	*tmp;

	while (*str)
	{
		str = skip_quotes(str);
		if (*str == '(')
			str += to_ending_par(str);
		tmp = str;
		if (starts_by(&tmp, needle))
			return (str);
		str++;
	}
	return (NULL);
}

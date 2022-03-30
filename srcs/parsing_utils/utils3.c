/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 08:46:59 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/30 14:38:32 by jmaia            ###   ########.fr       */
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
			str = to_ending_par(str);
		tmp = str;
		if (starts_by(&tmp, needle))
			return (str);
		str++;
	}
	return (NULL);
}

char	*sub_argument(char *str)
{
	char	*arg;
	char	quote;

	str = skip_spaces(str);
	str = sub(str, skip_argument(str));
	quote = 0;
	arg = "";
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			if (quote == 0)
				quote = *str;
			else if (quote == *str)
				quote = 0;
			else
				arg = straddchar(arg, *str);
		}
		else
			arg = straddchar(arg, *str);
		str++;
	}
	return (arg);
}

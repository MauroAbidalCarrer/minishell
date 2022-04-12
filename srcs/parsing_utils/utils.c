/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 17:05:09 by maabidal          #+#    #+#             */
/*   Updated: 2022/04/11 12:01:57 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"

char	*starts_by_f_redi(char *str)
{
	int		i;
	char	*f_redirections[4];

	i = -1;
	f_redirections[0] = "<<";
	f_redirections[2] = "<";
	f_redirections[1] = ">>";
	f_redirections[3] = ">";
	while (++i < 4)
		if (starts_by(&str, f_redirections[i]))
			return (str);
	return (NULL);
}

char	*starts_by_sep(char *str)
{
	if (starts_by(&str, "||"))
		return (str);
	if (*str == '|')
		return (str + 1);
	if (starts_by(&str, "&&"))
		return (str);
	return (NULL);
}

//to ending parenthes
char	*to_ending_par(char *str)
{
	int	count;

	count = 1;
	while (count)
	{
		++str;
		str = skip_quotes(str);
		count += (*str == '(');
		count -= (*str == ')');
	}
	return (str);
}

char	*strchr_qp(char *str, char c)
{
	while (*str)
	{
		str = skip_quotes(str);
		if (*str == '(')
			str = to_ending_par(str);
		if (*str == c)
			return (str);
		str++;
	}
	return (NULL);
}

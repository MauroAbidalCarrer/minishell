/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:56:21 by maabidal          #+#    #+#             */
/*   Updated: 2022/04/02 18:01:23 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"

char	*skip_quotes(char *str)
{
	if (*str == '\'' || *str == '\"')
		str = ft_strchr(str + 1, *str);
	return (str);
}

//skip quotes
char	*strstr_q(char *str, char *needle)
{
	char	*tmp;

	while (*str)
	{
		str = skip_quotes(str);
		tmp = str;
		if (starts_by(&tmp, needle))
			return (str);
		str++;
	}
	return (NULL);
}

char	*strchr_q(char *str, char needle)
{
	while (*str)
	{
		str = skip_quotes(str);
		if (*str == needle)
			return (str);
		str++;
	}
	return (NULL);
}

char	*skip_argument(char *str)
{
	str = skip_spaces(str);
	while (*str && *str != ' ')
	{
		str = skip_quotes(str);
		if (starts_by_sep(str) || starts_by_f_redi(str))
			break ;
		if (*str == '(' || *str == ')')
			break ;
		if (*str == '<' || *str == '>')
			break ;
		str++;
	}
	return (str);
}

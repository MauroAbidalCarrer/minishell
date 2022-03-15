/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:56:21 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/15 17:49:57 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"

char	*skip_quotes(char *str)
{
	if (*str == '\'' || *str == '\"')
		str = strchr(str + 1, *str);
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

char	*sub_argument(char *str)
{
	char	*arg;
	char	quote;

	str = skip_spaces(str);
	str = ft_substr(str, 0, skip_argument(str) - str);
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

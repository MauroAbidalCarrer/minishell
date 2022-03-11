/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:56:21 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/11 00:40:09 by maabidal         ###   ########.fr       */
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
	char	*tmp;

	str = skip_spaces(str);
	while (*str && *str != ' ')
	{
		str = skip_quotes(str);
		tmp = str;
		if (starts_by_sep(&tmp) || starts_by_f_redi(&tmp))
			break;
		if (*str == '(' || *str == ')')
			break ;
		if (*str == '<' || *str == '>')
			break ;
		str++;
	}
	return (str);
}

//utilse la lib de jeremy a la place
char	*sub_argument(char *str)
{
	char	*arg;
	int	i;
	int	len;

	str = skip_spaces(str);
	str = ft_substr(str, 0, skip_argument(str) - str);
	i = -1;
	len = 0;
	while (str[++i])
		len += (str[i] != '\'' && str[i] != '\"');
	arg = ft_malloc(sizeof(char) * (len + 1));
	arg[len] = 0;
	i = -1;
	len = 0;
	while (str[++i])
		if (str[i] != '\'' && str[i] != '\"')
			arg[len++] = str[i];
	return (arg);
}	

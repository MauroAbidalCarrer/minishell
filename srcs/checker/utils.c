/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:22:40 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/14 20:16:20 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	check_parentheses(char *str)
{
	int		count;

	count = 0;
	while (*str)
	{
		count += (*str == '(');
		count -= (*str == ')');
		if (count < 0)
		{
			ft_putstr_fd("Error: parentheses not closed\n", 2);
			return (0);
		}
		if (*str == '\'' || *str == '\"')
			str = strchr(str + 1, *str);
		str++;
	}
	if (count)
	{
		ft_putstr_fd("Error: parentheses not closed\n", 2);
		return (0);
	}
	return (1);
}

int	check_quotes(char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			str = strchr(str + 1, *str);
		if (str == NULL)
		{
			ft_putstr_fd("Error: quotes not closed\n", 2);
			return (0);
		}
		str++;
	}
	return (1);
}

char	*skip_cmd_s_no_p(char *cmd_s)
{

}

char	*sub_cmd_s(char *str)
{
	char	*begining;;
	int	is_parentheses;

	str = skip_spaces(str);
	begining = skip_spaces(str);
	while (*str && !starts_by_sep(str))
	{
		if (*str == '(')
		{
			if (is_parentheses)
				return (sub(begining, --str));
			else
			{
				is_parentheses = 1;
				str = to_ending_par(str);
			}
		}
		str = skip_argument(str);
		str = skip_spaces(str);
	}
	return (sub(begining, str));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:22:40 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/08 16:45:05 by maabidal         ###   ########.fr       */
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

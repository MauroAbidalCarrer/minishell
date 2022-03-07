/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 17:05:09 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/07 14:20:58 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	starts_by_f_redi(char **str)
{
	int		i;
	char	*f_redirections[4];

	i = -1;
	f_redirections[0] = "<<";
	f_redirections[2] = "<";
	f_redirections[1] = ">>";
	f_redirections[3] = ">";
	while (++i < 4)
		if (starts_by(str, f_redirections[i]))
			return (1);
	return (0);
}

int	starts_by_sep(char **str)
{
	if (starts_by(str, "||"))
		return (1);
	if (starts_by(str, "&&"))
		return (1);
	if (starts_by(str, "|"))
		return (1);
	return (0);
}

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
	return (0);
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

//to ending parenthes
int	to_ending_par(char *str)
{
	int	count;
	int	i;

	i = 0;
	count = 1;
	while (count)
	{
		i++;
		count += (str[i] == '(');
		count -= (str[i] == ')');
	}
	return (i);
}

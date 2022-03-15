/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:22:40 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/15 22:02:14 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	parentheses_closed(char *str)
{
	int		count;

	count = 0;
	while (*str)
	{
		count += (*str == '(');
		count -= (*str == ')');
		if (count < 0)
		{
			unexpected_err_msg(")");
			return (0);
		}
		if (*str == '\'' || *str == '\"')
			str = strchr(str + 1, *str);
		str++;
	}
	if (count)
	{
		ft_putstr_fd("Error: pqrentheses not closed\n", 2);
		return (0);
	}
	return (1);
}

int	quotes_closed(char *str)
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

void	unexpected_err_msg(char *err)
{
	char	*err_msg;

	err_msg = g_exe_name;
	err_msg = ft_strjoin(err_msg, ERR_PRE);
	err_msg = ft_strjoin(err_msg, err);
	err_msg = ft_strjoin(err_msg, "\'\n");
	ft_putstr_fd(err_msg, 2);
}

int	check_after_fredi(char *str)
{
	if (!*str)
		return (unexpected_err_msg("newline"), 0);
	if (*str == '(')
		return (unexpected_err_msg("("), 0);
	if (*str == ')')
		return (unexpected_err_msg(")"), 0);
	if (*str == '<' && str[1] != '<')
		return (unexpected_err_msg("<"), 0);
	if (*str == '<' && str[1] == '<')
		return (unexpected_err_msg("<<"), 0);
	if (*str == '>' && str[1] == '>')
		return (unexpected_err_msg(">>"), 0);
	if (*str == '>' && str[1] != '>')
		return (unexpected_err_msg(">"), 0);
	if (*str == '|' && str[1] != '|')
		return (unexpected_err_msg("|"), 0);
	if (*str == '|' && str[1] == '|')
		return (unexpected_err_msg("||"), 0);
	if (*str == '&' && str[1] == '&')
		return (unexpected_err_msg("&&"), 0);
	return (1);
}

int	check_p_in_cmd_s(char **str, int *p, int *nb_arg)
{
	if (**str == '(')
	{
		if (*p)
			return (unexpected_err_msg("("), 0);
		if (!should_exe_list(sub(*str + 1, to_ending_par(*str))))
			return (0);
		if (*nb_arg)
			return (unexpected_err_msg("("), 0);
		*p = 1;
		*str = to_ending_par(*str) + 1;
		printf("arg = %d\n", *nb_arg);
		(*nb_arg)++;
	}
	*str = skip_spaces(*str);
	if (**str && **str != ')' && !starts_by_sep(*str) && *p == 1)
	{
		if (**str == '(')
			return (unexpected_err_msg("("), 0);
		else if (starts_by_f_redi(*str))
			return (unexpected_err_msg(sub(*str, starts_by_f_redi(*str))), 0);
		else
			return (unexpected_err_msg(sub_argument(*str)), 0);
	}
	return (1);
}

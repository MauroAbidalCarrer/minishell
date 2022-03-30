/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:22:40 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/30 18:06:14 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	parentheses_closed(char *str, char *exename)
{
	int		count;

	count = 0;
	while (*str)
	{
		count += (*str == '(');
		count -= (*str == ')');
		if (count < 0)
		{
			err_msg(")", exename);
			return (0);
		}
		if (*str == '\'' || *str == '\"')
			str = ft_strchr(str + 1, *str);
		str++;
	}
	if (count)
	{
		ft_putstr_fd("Error: parentheses not closed\n", 2);
		return (0);
	}
	return (1);
}

int	quotes_closed(char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			str = ft_strchr(str + 1, *str);
		if (str == NULL)
		{
			ft_putstr_fd("Error: quotes not closed\n", 2);
			return (0);
		}
		str++;
	}
	return (1);
}

void	err_msg(char *err, char *exename)
{
	char	*err_msg;

	err_msg = exename;
	err_msg = ft_strjoin(err_msg, ERR_PRE);
	err_msg = ft_strjoin(err_msg, err);
	err_msg = ft_strjoin(err_msg, "\'\n");
	ft_putstr_fd(err_msg, 2);
}

int	check_after_fredi(char *str, char *exename)
{
	if (!*str)
		return (err_msg("newline", exename), 0);
	if (*str == '(')
		return (err_msg("(", exename), 0);
	if (*str == ')')
		return (err_msg(")", exename), 0);
	if (*str == '<' && str[1] != '<')
		return (err_msg("<", exename), 0);
	if (*str == '<' && str[1] == '<')
		return (err_msg("<<", exename), 0);
	if (*str == '>' && str[1] == '>')
		return (err_msg(">>", exename), 0);
	if (*str == '>' && str[1] != '>')
		return (err_msg(">", exename), 0);
	if (*str == '|' && str[1] != '|')
		return (err_msg("|", exename), 0);
	if (*str == '|' && str[1] == '|')
		return (err_msg("||", exename), 0);
	if (*str == '&' && str[1] == '&')
		return (err_msg("&&", exename), 0);
	return (1);
}

int	check_p_in_cmd_s(char **str, int *p, int *nb_arg, char *exename)
{
	if (**str == '(')
	{
		if (*p)
			return (err_msg("(", exename), 0);
		if (!should_exe_list(sub(*str + 1, to_ending_par(*str)), exename))
			return (0);
		if (*nb_arg)
			return (err_msg("(", exename), 0);
		*p = 1;
		*str = to_ending_par(*str) + 1;
		(*nb_arg)++;
	}
	*str = skip_spaces(*str);
	if (**str && **str != ')' && !starts_by_sep(*str) && *p == 1)
	{
		if (**str == '(')
			return (err_msg("(", exename), 0);
		else if (starts_by_f_redi(*str))
			return (err_msg(sub(*str, starts_by_f_redi(*str)), exename), 0);
		else
			return (err_msg(sub_argument(*str), exename), 0);
	}
	return (1);
}

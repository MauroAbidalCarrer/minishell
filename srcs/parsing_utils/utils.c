/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 17:05:09 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/14 19:55:34 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"

char	*starts_by_f_redi(char *str)
{
	int		i;
	char	*f_redirections[4];
	char	*tmp;

	i = -1;
	f_redirections[0] = "<<";
	f_redirections[2] = "<";
	f_redirections[1] = ">>";
	f_redirections[3] = ">";
	while (++i < 4)
	{
		tmp = starts_by(&str, f_redirections[i]);
		if (tmp)
			return (tmp);
	}
	return (NULL);
}

char	*starts_by_sep(char *str)
{
	char	*tmp;

	if (*tmp == '|')
		return (tmp + 1);
	tmp = starts_by(str, "||");
	if (tmp)
		return (tmp);
	tmp = starts_by(str, "&&");
	if (tmp)
		return (tmp);
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
		count += (*str == '(');
		count -= (*str == ')');
	}
	return (str);
}

int	get_env_var(char *key, char **dst, char **env)
{
	int	i;
	int	j;

	if (env == NULL)
		return (1);
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && key[j] && env[i][j] == key[j])
		{
			if (key[j + 1] == 0)
			{
				*dst = env[i] + j + 2;
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

char	*strchr_qp(char *str, char c)
{
	while (*str)
	{
		str = skip_quotes(str);
		if (*str == '(')
			str += to_ending_par(str);
		if (*str == c)
			return (str);
		str++;
	}
	return (NULL);
}

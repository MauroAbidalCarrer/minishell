/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 17:05:09 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/11 04:04:31 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"

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

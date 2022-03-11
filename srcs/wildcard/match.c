/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:28:56 by jmaia             #+#    #+#             */
/*   Updated: 2022/03/11 15:11:52 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

static int	do_recur_match(char const *str, char const *pattern);

int	do_match(char const *str, char const *pattern)
{
	if (!ft_strcmp(str, ".") || !ft_strcmp(str, "..")
		|| (*str == '.' && *pattern != '.'))
		return (0);
	return (do_recur_match(str, pattern));
}

static int	do_recur_match(char const *str, char const *pattern)
{
	if (*pattern == '*')
		return (do_recur_match(str, pattern + 1)
			|| (*str && (do_recur_match(str + 1, pattern)
					|| do_recur_match(str + 1, pattern + 1))));
	if (!*str || !*pattern)
		return (!*pattern && !*str);
	return (*str == *pattern && do_recur_match(str + 1, pattern + 1));
}

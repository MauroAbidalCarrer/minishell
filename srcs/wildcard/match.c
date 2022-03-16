/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:28:56 by jmaia             #+#    #+#             */
/*   Updated: 2022/03/15 15:27:16 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

static int	do_recur_match(char const *str, char const *pattern, char englober);

int	do_match(char const *str, char const *pattern)
{
	if (!ft_strcmp(str, ".") || !ft_strcmp(str, "..")
		|| (*str == '.' && *pattern != '.'))
		return (0);
	return (do_recur_match(str, pattern, 0));
}

static int	do_recur_match(char const *str, char const *pattern, char englober)
{
	if (!englober && (*pattern == '"' || *pattern == '\''))
		return (do_recur_match(str, pattern + 1, *pattern));
	if (englober == *pattern && *pattern)
		return (do_recur_match(str, pattern + 1, 0));
	if (*pattern == '*' && !englober)
		return (do_recur_match(str, pattern + 1, englober)
			|| (*str && (do_recur_match(str + 1, pattern, englober)
					|| do_recur_match(str + 1, pattern + 1, englober))));
	if (!*str || !*pattern)
		return (!*pattern && !*str);
	return (*str == *pattern && do_recur_match(str + 1, pattern + 1, englober));
}

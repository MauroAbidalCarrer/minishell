/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:28:56 by jmaia             #+#    #+#             */
/*   Updated: 2022/03/08 16:29:52 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

int	do_match(char const *str, char const *pattern)
{
	if (*pattern == '*')
		return (do_match(str, pattern + 1)
			|| (*str && (do_match(str + 1, pattern)
					|| do_match(str + 1, pattern + 1))));
	if (!*str || !*pattern)
		return (!*pattern && !*str);
	return (*str == *pattern && do_match(str + 1, pattern + 1));
}

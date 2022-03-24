/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_it2_it_is_back.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:23:29 by jmaia             #+#    #+#             */
/*   Updated: 2022/03/24 21:27:37 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

char const	*get_next_word(char const *cur_word)
{
	char const	*next_word;
	char		englober;

	englober = 0;
	next_word = cur_word;
	while (*next_word && (!ft_isspace(*next_word) || englober))
	{
		if (*next_word == englober)
			englober = 0;
		else if (!englober && (*next_word == '"' || *next_word == '\''))
			englober = *next_word;
		next_word++;
	}
	while (*next_word && ft_isspace(*next_word))
		next_word++;
	if (!*next_word)
		return (0);
	return (next_word);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_it2_it_is_back.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:23:29 by jmaia             #+#    #+#             */
/*   Updated: 2022/04/12 22:09:11 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

char	*get_next_word(char *cur_word)
{
	char	*next_word;
	char	englober;

	englober = 0;
	next_word = cur_word;
	while (*next_word && ((!ft_isspace(*next_word)
				&& *next_word != '>' && *next_word != '<') || englober))
	{
		if (*next_word == englober)
			englober = 0;
		else if (!englober && (*next_word == '"' || *next_word == '\''))
			englober = *next_word;
		next_word++;
	}
	if (!*next_word)
		return (0);
	return (next_word);
}

void	append_full_quoted_word(t_dynamic_buffer *buffer, char *word)
{
	int	i;

	append(buffer, "'");
	i = 0;
	while (word[i])
	{
		if (word[i] == '\'')
		{
			append(buffer, "'");
			append(buffer, "\"");
		}
		append(buffer, &word[i]);
		if (word[i] == '\'')
		{
			append(buffer, "\"");
			append(buffer, "'");
		}
		i++;
	}
	append(buffer, "'");
}

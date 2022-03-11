/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_it.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:38:36 by jmaia             #+#    #+#             */
/*   Updated: 2022/03/11 15:15:15 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

static void			get_space(char const *str, char *space, char **space_pos);
static int			append_pattern(t_dynamic_buffer *buffer,
						char const *pattern);
static int			append_word(t_dynamic_buffer *buffer, char const *word);
static char const	*get_next_word(char const *cur_word);

char	*wild_it(char const *pattern)
{
	char				space;
	char				*space_pos;
	char				*wilded_str;
	char const			*cur_word;
	t_dynamic_buffer	buffer;

	buffer = get_buffer(sizeof(char));
	if (!buffer.buffer)
		return (0);
	cur_word = pattern;
	while (cur_word)
	{
		get_space(cur_word, &space, &space_pos);
		*space_pos = 0;
		if (ft_strchr(cur_word, '*'))
			append_pattern(&buffer, cur_word);
		else
			append_word(&buffer, cur_word);
		*space_pos = space;
		cur_word = get_next_word(cur_word);
	}
	wilded_str = as_str(&buffer);
	free(buffer.buffer);
	return (wilded_str);
}

static void	get_space(char const *str, char *space, char **space_pos)
{
	*space_pos = (char *) str;
	while (**space_pos && !ft_isspace(**space_pos))
		(*space_pos)++;
	*space = **space_pos;
}

static int	append_pattern(t_dynamic_buffer *buffer, char const *pattern)
{
	DIR				*dir;
	char			space_char;
	int				is_first;
	struct dirent	*dirent;

	space_char = ' ';
	dir = opendir(".");
	if (!dir)
		return (1);
	errno = 0;
	dirent = readdir(dir);
	is_first = 1;
	while (dirent)
	{
		if (do_match(dirent->d_name, pattern))
		{
			if (!is_first)
				append(buffer, &space_char);
			is_first = 0;
			append_word(buffer, dirent->d_name);
		}
		dirent = readdir(dir);
	}
	closedir(dir);
	return (errno != 0);
}

static int	append_word(t_dynamic_buffer *buffer, char const *word)
{
	int			err;
	char const	*cur_c;

	err = 0;
	cur_c = word;
	while (*cur_c && !err)
	{
		err |= append(buffer, (char *) cur_c);
		cur_c++;
	}
	return (err);
}

static char const	*get_next_word(char const *cur_word)
{
	char const	*next_word;

	next_word = cur_word;
	while (*next_word && !ft_isspace(*next_word))
		next_word++;
	while (*next_word && ft_isspace(*next_word))
		next_word++;
	if (!*next_word)
		return (0);
	return (next_word);
}

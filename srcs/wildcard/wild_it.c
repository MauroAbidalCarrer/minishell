/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_it.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:38:36 by jmaia             #+#    #+#             */
/*   Updated: 2022/03/23 18:14:17 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

static int			wild_word(char const *cur_word, int is_not_first,
						t_dynamic_buffer *buffer);
static void			get_space(char const *str, char *space, char **space_pos);
static int			append_pattern(t_dynamic_buffer *buffer,
						char const *pattern);
static int			append_word(t_dynamic_buffer *buffer, char const *word);

char	*wild_it(char const *pattern)
{
	char				*wilded_str;
	char const			*cur_word;
	t_dynamic_buffer	buffer;
	int					is_not_first;

	buffer = get_buffer(sizeof(char));
	if (!buffer.buffer)
		return (0);
	cur_word = pattern;
	is_not_first = 0;
	while (cur_word)
	{
		wild_word(cur_word, is_not_first++, &buffer);
		cur_word = get_next_word(cur_word);
	}
	wilded_str = as_str(&buffer);
	ft_free(buffer.buffer);
	return (wilded_str);
}

static int	wild_word(char const *cur_word, int is_not_first,
				t_dynamic_buffer *buffer)
{
	char	space;
	char	space_char;
	char	*space_pos;
	int		err;

	space_char = ' ';
	if (is_not_first)
		append(buffer, &space_char);
	get_space(cur_word, &space, &space_pos);
	*space_pos = 0;
	if (ft_strchr(cur_word, '*') || ft_strchr(cur_word, '"')
		|| ft_strchr(cur_word, '\''))
		err = append_pattern(buffer, cur_word);
	else
		err = append_word(buffer, cur_word);
	*space_pos = space;
	return (err);
}

static void	get_space(char const *str, char *space, char **space_pos)
{
	char	englober;

	englober = 0;
	*space_pos = (char *) str;
	while (**space_pos && (!ft_isspace(**space_pos) || englober))
	{
		if (**space_pos == englober)
			englober = 0;
		else if (!englober && (**space_pos == '"' || **space_pos == '\''))
			englober = **space_pos;
		(*space_pos)++;
	}
	*space = **space_pos;
}

int	append_and_quote_str(t_dynamic_buffer *buffer, char *str);

static int	append_pattern(t_dynamic_buffer *buffer, char const *pattern)
{
	DIR		*dir;
	int		is_first;
	t_list	*files;

	dir = opendir(".");
	if (!dir)
		return (1);
	files = get_sorted_files(dir);
	is_first = 1;
	while (files)
	{
		if (do_match((char *) files->content, pattern))
		{
			if (!is_first)
				append(buffer, " ");
			is_first = 0;
			append_and_quote_str(buffer, (char *) files->content);
//			append_word(buffer, (char *) files->content);
		}
		files = files->next;
	}
	if (is_first)
		append_word(buffer, pattern);
	return (closedir(dir) != 0);
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

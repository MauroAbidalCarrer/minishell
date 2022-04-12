/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_it.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:38:36 by jmaia             #+#    #+#             */
/*   Updated: 2022/04/12 22:34:59 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "builtins.h"

static void	get_separator(char const *str, char *space, char **space_pos);
static int	append_pattern(t_dynamic_buffer *buffer,
				char const *pattern);
static void	append_word(t_dynamic_buffer *buffer, char const *word);

char	*wild_it(char *pattern)
{
	char				*wilded_str;
	char				*cur_word;
	t_dynamic_buffer	buffer;

	buffer = get_buffer(sizeof(char));
	if (pattern && !test_if_wildcard_ambiguous(pattern))
	{
		cur_word = pattern;
		while (cur_word)
		{
			if (ft_isspace(*cur_word) || *cur_word == '<' || *cur_word == '>')
				append(&buffer, cur_word++);
			else
			{
				wild_word(cur_word, &buffer);
				cur_word = get_next_word(cur_word);
			}
		}
	}
	wilded_str = as_str(&buffer);
	ft_free(buffer.buffer);
	return (wilded_str);
}

// Returns number of words
int	wild_word(char const *cur_word, t_dynamic_buffer *buffer)
{
	char	separator;
	char	*separator_pos;
	int		n_words;

	get_separator(cur_word, &separator, &separator_pos);
	*separator_pos = 0;
	n_words = 1;
	if (ft_strchr(cur_word, '*') || ft_strchr(cur_word, '"')
		|| ft_strchr(cur_word, '\''))
		n_words = append_pattern(buffer, cur_word);
	else
		append_word(buffer, cur_word);
	*separator_pos = separator;
	return (n_words);
}

static void	get_separator(char const *str, char *separator,
	char **separator_pos)
{
	char	englober;

	englober = 0;
	*separator_pos = (char *) str;
	while (**separator_pos
		&& ((!ft_isspace(**separator_pos)
				&& **separator_pos != '<' && **separator_pos != '>')
			|| englober))
	{
		if (**separator_pos == englober)
			englober = 0;
		else if (!englober && (**separator_pos == '"'
				|| **separator_pos == '\''))
			englober = **separator_pos;
		(*separator_pos)++;
	}
	*separator = **separator_pos;
}

static int	append_pattern(t_dynamic_buffer *buffer, char const *pattern)
{
	DIR		*dir;
	int		n_matches;
	t_list	*files;

	dir = opendir(".");
	if (!dir)
		return (-1);
	files = get_sorted_files(dir);
	n_matches = 0;
	while (files)
	{
		if (do_match((char *) files->content, pattern))
		{
			if (n_matches++ != 0)
				append(buffer, " ");
			append_full_quoted_word(buffer, (char *) files->content);
		}
		files = files->next;
	}
	if (n_matches == 0)
		append_word(buffer, pattern);
	if (n_matches == 0)
		n_matches = 1;
	closedir(dir);
	return (n_matches);
}

static void	append_word(t_dynamic_buffer *buffer, char const *word)
{
	char const	*cur_c;

	cur_c = word;
	while (*cur_c)
	{
		append(buffer, (char *) cur_c);
		cur_c++;
	}
}

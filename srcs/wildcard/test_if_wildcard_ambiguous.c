/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_if_wildcard_ambiguous.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 10:44:59 by jmaia             #+#    #+#             */
/*   Updated: 2022/04/12 22:22:31 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

static void	update_redirection_status(t_redirection_status *redir_status,
				char c);
static int	test_if_word_ambiguous(char *cur_word);

int	test_if_wildcard_ambiguous(char *pattern)
{
	char					*cur;
	char					*cur_word;
	int						is_ambiguous;
	t_redirection_status	redir_status;

	cur = pattern;
	cur_word = cur;
	is_ambiguous = 0;
	redir_status = NOT_IN_REDIRECTION;
	while (*cur && !is_ambiguous)
	{
		if (ft_isspace(*cur) || *cur == '<' || *cur == '>')
			cur_word = 0;
		else if (cur_word == 0)
			cur_word = cur;
		if (*cur == '\'' || *cur == '"')
			cur = ft_strchr(cur + 1, *cur);
		update_redirection_status(&redir_status, *cur);
		if (*cur == '*' && redir_status != NOT_IN_REDIRECTION)
			is_ambiguous = test_if_word_ambiguous(cur_word);
		cur++;
	}
	return (is_ambiguous);
}

static void	update_redirection_status(t_redirection_status *redir_status,
	char c)
{
	if (c == '>' || c == '<')
		*redir_status = BEFORE_WORD;
	else if (!ft_isspace(c) && *redir_status == BEFORE_WORD)
		*redir_status = IN_WORD;
	else if (ft_isspace(c) && *redir_status == IN_WORD)
		*redir_status = NOT_IN_REDIRECTION;
}

static int	test_if_word_ambiguous(char *cur_word)
{
	int					is_ambiguous;
	int					n_words;
	t_dynamic_buffer	buffer;

	buffer = get_buffer(sizeof(char));
	n_words = wild_word(cur_word, &buffer);
	is_ambiguous = 0;
	if (n_words > 1)
	{
		write_error(NULL, cur_word, "ambiguous redirect");
		is_ambiguous = 1;
	}
	ft_free(buffer.buffer);
	return (is_ambiguous);
}

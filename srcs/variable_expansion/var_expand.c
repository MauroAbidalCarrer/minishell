/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:44:02 by jmaia             #+#    #+#             */
/*   Updated: 2022/04/07 12:18:39 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "var_expand.h"

char	*var_expand(char *pattern, t_env env)
{
	char				*expanded_str;
	int					err;
	t_dynamic_buffer	buffer;

	buffer = get_buffer(sizeof(char));
	if (!buffer.buffer)
		return (0);
	err = process_pattern(&buffer, env, pattern);
	if (err)
		return (0);
	expanded_str = as_str(&buffer);
	ft_free(buffer.buffer);
	return (expanded_str);
}

int	process_pattern(t_dynamic_buffer *buffer, t_env env, char *pattern)
{
	t_heredoc_status	heredoc_status;
	int					in_dquote;

	heredoc_status = NOT_IN_HEREDOC;
	in_dquote = 0;
	while (*pattern)
	{
		update_heredoc_status(pattern, &heredoc_status);
		if (!in_dquote && is_ambiguous(pattern, env, heredoc_status))
		{
			write_error(NULL, is_ambiguous(pattern, env, heredoc_status),
				"ambiguous redirect");
			ft_free(buffer->buffer);
			return (1);
		}
		if (*pattern == '\"')
			in_dquote = !in_dquote;
		if (*pattern == '$' && heredoc_status == NOT_IN_HEREDOC)
			append_var_and_move(buffer, &pattern, env, in_dquote);
		else if (!in_dquote && *pattern == '\'')
			append_quoted_str_and_move(buffer, &pattern);
		else
			append(buffer, pattern++);
	}
	return (0);
}

char	*is_ambiguous(char *str, t_env env, t_heredoc_status heredoc_status)
{
	char				*cur;
	t_ambiguous_state	ambiguous_state;

	if ((*str != '>' && *str != '<') || *(str + 1) == '>'
		|| heredoc_status != NOT_IN_HEREDOC)
		return (0);
	while (ft_isspace(*++str))
		;
	cur = str;
	ambiguous_state = HAS_NO_NORMAL_CHARACTERS;
	while (*cur && !ft_isspace(*cur) && ambiguous_state != IS_AMBIGUOUS)
	{
		if (*cur == '\'' || *cur == '"')
			cur = ft_strchr(cur + 1, *cur);
		if (*cur == '\'' || *cur == '"')
			ambiguous_state = HAS_NORMAL_CHARACTERS;
		update_ambiguous_state(&ambiguous_state, &cur, env);
		cur++;
	}
	if (ambiguous_state != HAS_NORMAL_CHARACTERS)
		return (str);
	else
		return (0);
}

int	append_quoted_str_and_move(t_dynamic_buffer *d_buffer, char **str)
{
	char	*quote_pos;
	char	c;

	quote_pos = ft_strchr(*str + 1, '\'');
	c = *(quote_pos + 1);
	*(quote_pos + 1) = 0;
	append_str(d_buffer, *str);
	*(quote_pos + 1) = c;
	*str = quote_pos + 1;
	return (0);
}

int	append_var_and_move(t_dynamic_buffer *buffer, char **cur_c,
				t_env env, int in_dquote)
{
	char	*status_code_str;
	int		err;

	status_code_str = ft_itoa(env.exit_status);
	*cur_c += 1;
	if (**cur_c == '?')
	{
		(*cur_c)++;
		return (append_str(buffer, status_code_str));
	}
	if (!is_almost_valid_char_for_name(**cur_c)
		&& *(*cur_c + 1) != '\'' && *(*cur_c + 1) != '"')
	{
		err = append(buffer, "$");
		return (err);
	}
	return (append_var_and_move2(buffer, env, cur_c, in_dquote));
}

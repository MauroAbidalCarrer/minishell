/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:44:02 by jmaia             #+#    #+#             */
/*   Updated: 2022/04/05 18:31:46 by jmaia            ###   ########.fr       */
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
	int	in_heredoc;
	int	in_dquote;

	in_heredoc = 0;
	in_dquote = 0;
	while (*pattern)
	{
		if (is_ambiguous(pattern, env))
		{
			write_error(NULL, is_ambiguous(pattern, env), "ambiguous redirect");
			ft_free(buffer->buffer);
			return (1);
		}
		if (!ft_isspace(*pattern) && ft_isspace(*(pattern + 1)))
			in_heredoc = 0;
		if (*pattern == '\"')
			in_dquote = !in_dquote;
		if (*pattern == '$' && !in_heredoc)
			append_var_and_move(buffer, &pattern, env, in_dquote);
		else if (!in_dquote && *pattern == '\'')
			append_quoted_str_and_move(buffer, &pattern);
		else
			append(buffer, pattern++);
	}
	return (0);
}

char	*is_ambiguous(char *str, t_env env)
{
	char				*cur;
	char				*cur_expanded;
	char				*end_space_pos;
	char				space;
	char				*expanded;

	if ((*str != '>' && *str != '<') || *(str + 1) == '>' || *(str + 1) == '<')
		return (0);
	cur = str + 1;
	while (ft_isspace(*cur))
		cur++;
	end_space_pos = cur;
	while (*end_space_pos && !ft_isspace(*end_space_pos))
		end_space_pos++;
	space = *end_space_pos;
	*end_space_pos = 0;
	expanded = var_expand(cur, env);
	*end_space_pos = space;
	if (!*expanded)
		return (cur);
	cur_expanded = expanded;
	while (*cur_expanded)
		if (ft_isspace(*cur_expanded++))
			return (cur);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:44:02 by jmaia             #+#    #+#             */
/*   Updated: 2022/03/29 22:48:19 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "var_expand.h"

static int	append_var_and_move(t_dynamic_buffer *buffer, char **cur_c,
				char **env, char *status_code, int in_dquote);
static int	is_almost_valid_char_for_name(char c);
int	append_and_quote_str(t_dynamic_buffer *buffer, char *str);
static int	append_str(t_dynamic_buffer *buffer, char *str);
static int	append_quoted_str_and_move(t_dynamic_buffer *d_buffer, char **str);
static char	*is_ambiguous(char *str, char **env);

char	*var_expand(char *pattern, char **env, int status_code)
{
	char				*cur_c;
	char				*expanded_str;
	char				*status_code_str;
	int					in_dquote;
	int					in_heredoc_word;
	int					in_redir;
	t_dynamic_buffer	buffer;

	buffer = get_buffer(sizeof(char));
	if (!buffer.buffer)
		return (0);
	status_code_str = ft_itoa(status_code);
	if (!status_code_str)
		ft_free(buffer.buffer);
	if (!status_code_str)
		return (0);
	cur_c = pattern;
	in_dquote = 0;
	in_heredoc_word = 0;
	in_redir = 0;
	while (*cur_c)
	{
		if (!ft_isspace(*cur_c) && ft_isspace(*(cur_c + 1)))
			in_heredoc_word = 0;
		if (*cur_c == '\"')
			in_dquote = !in_dquote;
		if (!in_dquote && *cur_c == '\'')
			append_quoted_str_and_move(&buffer, &cur_c);
		if (is_ambiguous(cur_c, env))
		{
//			write_error(NULL, is_ambiguous(cur_c, env), "ambiguous redirect");
			printf("(A REMOVE) bash: %s: ambiguous redirect\n", is_ambiguous(cur_c, env));
			ft_free(buffer.buffer);
			return (0);
		}
		else if (*cur_c == '$' && !in_heredoc_word)
		{
			append_var_and_move(&buffer, &cur_c, env, status_code_str, in_dquote);
			continue;
		}
		else
			append(&buffer, cur_c++);
	}
	expanded_str = as_str(&buffer);
	ft_free(buffer.buffer);
	ft_free(status_code_str);
	return (expanded_str);
}

static char	*is_ambiguous(char *str, char **env)
{
	char				*cur;
	char				*cur_expanded;
	char				*end_space_pos;
	char				space;
	char				*expanded;

	if ((*str != '>' && *str != '<') || (*str && *(str + 1) == '>'))
		return (0);
	cur = str + 1;
	while (ft_isspace(*cur))
		cur++;
	end_space_pos = cur;
	while (*end_space_pos && !ft_isspace(*end_space_pos))
		end_space_pos++;
	space = *end_space_pos;
	*end_space_pos = 0;
	expanded = var_expand(cur, env, 0);
	*end_space_pos = space;
	if (!*expanded)
		return (cur);
	cur_expanded = expanded;
	while (*cur_expanded)
		if (ft_isspace(*cur_expanded++))
			return (cur);
	return (0);
}

static int	append_quoted_str_and_move(t_dynamic_buffer *d_buffer, char **str)
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

static int	append_var_and_move(t_dynamic_buffer *buffer, char **cur_c,
				char **env, char *status_code, int in_dquote)
{
	char	end_char;
	char	*end_pos;
	char	*value;
	int		err;

	*cur_c += 1;
	if (**cur_c == '?')
	{
		(*cur_c)++;
		return (append_str(buffer, status_code));
	}
	if (!is_almost_valid_char_for_name(**cur_c))
	{
		err = append(buffer, "$");
		return (err);
	}
	end_pos = *cur_c;
	while (is_almost_valid_char_for_name(*end_pos))
		end_pos++;
	end_char = *end_pos;
	*end_pos = 0;
	err = get_env_var(*cur_c, &value, env);
	*end_pos = end_char;
	*cur_c = end_pos;
	if (err)
		return (err);
	if (!in_dquote)
		err = append_and_quote_str(buffer, value);
	else
		err = append_str(buffer, value);
	return (err);
}

static int	is_almost_valid_char_for_name(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || c == '_');
}

static int	append_str(t_dynamic_buffer *buffer, char *str)
{
	char	*cur_c;
	int		err;

	cur_c = str;
	err = 0;
	while (*cur_c && !err)
		err = append(buffer, cur_c++);
	return (err);
}

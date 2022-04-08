/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand_in_heredoc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 10:05:00 by jmaia             #+#    #+#             */
/*   Updated: 2022/04/08 16:38:36 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "var_expand.h"

static void	append_pattern_and_move_in_heredoc_mode(t_dynamic_buffer *buffer,
				char **pattern, t_env env);
static void	append_var_and_move_in_heredoc_mode(t_dynamic_buffer *buffer,
				char **pattern, t_env env);

char	*var_expand_in_heredoc(char *pattern, t_env env)
{
	char				*cur;
	char				*expanded;
	t_dynamic_buffer	buffer;

	buffer = get_buffer(sizeof(char));
	cur = pattern;
	while (*cur)
		append_pattern_and_move_in_heredoc_mode(&buffer, &cur, env);
	expanded = as_str(&buffer);
	ft_free(buffer.buffer);
	return (expanded);
}

static void	append_pattern_and_move_in_heredoc_mode(t_dynamic_buffer *buffer,
				char **pattern, t_env env)
{
	if (**pattern != '$')
		append(buffer, (*pattern)++);
	else
		append_var_and_move_in_heredoc_mode(buffer, pattern, env);
}

static void	append_var_and_move_in_heredoc_mode(t_dynamic_buffer *buffer,
				char **pattern, t_env env)
{
	(*pattern)++;
	if (**pattern == '?')
	{
		append_exit_status(buffer, env);
		(*pattern)++;
	}
	else if (!is_almost_valid_char_for_name(**pattern))
		append(buffer, "$");
	else
		append_env_var_and_move_in_heredoc_mode(buffer, pattern, env);
}

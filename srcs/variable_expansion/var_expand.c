/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:44:02 by jmaia             #+#    #+#             */
/*   Updated: 2022/03/20 19:22:57 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "var_expand.h"

static int	append_var_and_move(t_dynamic_buffer *buffer, char **cur_c,
				char **env, char *status_code);
static int	is_almost_valid_char_for_name(char c);
static int	append_str(t_dynamic_buffer *buffer, char *str);

char	*var_expand(char *pattern, char **env, int status_code)
{
	char				*cur_c;
	char				*expanded_str;
	char				*status_code_str;
	t_dynamic_buffer	buffer;

	buffer = get_buffer(sizeof(char));
	if (!buffer.buffer)
		return (0);
	status_code_str = ft_itoa(status_code);
	if (!status_code_str)
		free(buffer.buffer);
	if (!status_code_str)
		return (0);
	cur_c = pattern;
	while (*cur_c)
	{
		if (*cur_c == '$')
			append_var_and_move(&buffer, &cur_c, env, status_code_str);
		else
			append(&buffer, cur_c++);
	}
	expanded_str = as_str(&buffer);
	free(buffer.buffer);
	ft_free(status_code_str);
	return (expanded_str);
}

static int	append_var_and_move(t_dynamic_buffer *buffer, char **cur_c,
				char **env, char *status_code)
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

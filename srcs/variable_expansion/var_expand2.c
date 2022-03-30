/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 16:56:37 by jmaia             #+#    #+#             */
/*   Updated: 2022/03/30 16:56:42 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "var_expand.h"

int	append_var_and_move2(t_dynamic_buffer *buffer, t_env env,
				char **cur_c, int in_dquote)
{
	char	end_char;
	char	*end_pos;
	char	*value;
	int		err;

	end_pos = *cur_c;
	while (is_almost_valid_char_for_name(*end_pos))
		end_pos++;
	end_char = *end_pos;
	*end_pos = 0;
	err = get_env_var(*cur_c, &value, *env.env);
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

int	is_almost_valid_char_for_name(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || c == '_');
}

int	append_str(t_dynamic_buffer *buffer, char *str)
{
	char	*cur_c;
	int		err;

	cur_c = str;
	err = 0;
	while (*cur_c && !err)
		err = append(buffer, cur_c++);
	return (err);
}

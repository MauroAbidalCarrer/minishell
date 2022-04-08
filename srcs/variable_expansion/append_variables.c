/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 12:42:00 by jmaia             #+#    #+#             */
/*   Updated: 2022/04/08 12:44:43 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "var_expand.h"

static char	*get_var_name(char *pattern);

void	append_exit_status(t_dynamic_buffer *buffer, t_env env)
{
	char	*exit_status_str;

	exit_status_str = ft_itoa(env.exit_status);
	append_str(buffer, exit_status_str);
	ft_free(exit_status_str);
}

void	append_env_var_and_move_in_heredoc_mode(t_dynamic_buffer *buffer,
				char **pattern, t_env env)
{
	char	*var_name;
	char	*value;
	int		err;

	var_name = get_var_name(*pattern);
	*pattern += ft_strlen(var_name);
	err = get_env_var(var_name, &value, *env.env);
	if (!err)
		append_str(buffer, value);
	ft_free(var_name);
}

static char	*get_var_name(char *pattern)
{
	int		len;
	char	*var_name;

	len = 0;
	while (is_almost_valid_char_for_name(pattern[len]))
		len++;
	var_name = ft_malloc(sizeof(*var_name) * (len + 1));
	ft_memcpy(var_name, pattern, sizeof(char) * len);
	var_name[len] = 0;
	return (var_name);
}

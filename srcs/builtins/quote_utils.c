/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 21:55:23 by jmaia             #+#    #+#             */
/*   Updated: 2022/04/04 16:39:56 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	is_special_char(char c);
static void	append_next_char(t_dynamic_buffer *buffer, char *str, int i);

char	*escape_quote_and_backslash(char *var)
{
	char			*escaped_var;
	int				i;
	int				j;
	unsigned int	n_quotes;

	i = 0;
	n_quotes = 0;
	while (var[i])
	{
		if (var[i] == '"' || var[i] == '\\')
			n_quotes++;
		i++;
	}
	escaped_var = ft_malloc(sizeof(*escaped_var)
			* (ft_strlen(var) + n_quotes + 1));
	i = 0;
	j = 0;
	while (var[i])
	{
		if (var[i] == '"' || var[i] == '\\')
			escaped_var[j++] = '\\';
		escaped_var[j++] = var[i++];
	}
	escaped_var[ft_strlen(var) + n_quotes] = 0;
	return (escaped_var);
}

char	*quote_value(char *var)
{
	char	*quoted_var;
	int		i;
	int		j;
	int		sign_found;

	quoted_var = ft_malloc(sizeof(*quoted_var) * ft_strlen(var) + 3);
	i = 0;
	j = 0;
	sign_found = 0;
	while (var[j])
	{
		quoted_var[i++] = var[j++];
		if (var[j - 1] == '=' && !sign_found++)
			quoted_var[i++] = '"';
	}
	quoted_var[i++] = '"';
	quoted_var[i] = 0;
	return (quoted_var);
}

int	append_and_quote_str(t_dynamic_buffer *buffer, char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		append_next_char(buffer, str, i);
		i++;
	}
	return (0);
}

static void	append_next_char(t_dynamic_buffer *buffer, char *str, int i)
{
	if (is_special_char(str[i]))
	{
		if (str[i] == '\'')
			append(buffer, "\"");
		else
			append(buffer, "'");
		append(buffer, &str[i]);
		if (str[i] == '\'')
			append(buffer, "\"");
		else
			append(buffer, "'");
	}
	else
		append(buffer, &str[i]);
}

static int	is_special_char(char c)
{
	return (c == '&' || c == '|' || c == '(' || c == ')' || c == '<'
		|| c == '>' || c == '\'' || c == '"');
}

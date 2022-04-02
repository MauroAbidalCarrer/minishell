/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 21:55:23 by jmaia             #+#    #+#             */
/*   Updated: 2022/04/02 18:19:55 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	is_special_char(char c);
static void	append_next_char(t_dynamic_buffer *buffer, char **array, int i,
				int j);

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
	char	**array;
	int		i;
	int		j;

	array = ft_split_white(str);
	i = 0;
	while (array[i])
	{
		j = 0;
		while (array[i][j])
		{
			append_next_char(buffer, array, i, j);
			j++;
		}
		if (array[i + 1])
			append(buffer, " ");
		i++;
	}
	ft_free(array);
	return (0);
}

static void	append_next_char(t_dynamic_buffer *buffer, char **array, int i,
	int j)
{
	if (is_special_char(array[i][j]))
	{
		if (array[i][j] == '\'')
			append(buffer, "\"");
		else
			append(buffer, "'");
		append(buffer, &array[i][j]);
		if (array[i][j] == '\'')
			append(buffer, "\"");
		else
			append(buffer, "'");
	}
	else
		append(buffer, &array[i][j]);
}

static int	is_special_char(char c)
{
	return (c == '&' || c == '|' || c == '(' || c == ')' || c == '<'
		|| c == '>' || c == '\'' || c == '"');
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_white.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 21:24:55 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/22 20:04:33 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static char	*skip(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && ft_isspace(*str) == ft_isspace(str[i]))
		i++;
	return ((char *)str + i);
}

static int	get_nb_words(const char *str)
{
	size_t	nb;
	int		i;

	i = 0;
	nb = (*str && !ft_isspace(*str));
	while (str[i] && str[i + 1])
	{
		nb += (ft_isspace(str[i]) && !ft_isspace(str[i + 1]));
		i++;
	}
	return (nb);
}

static char	*dup_until_sep(char const *str)
{
	ssize_t	len;
	char	*word;

	len = 0;
	while (str[len] && !ft_isspace(str[len]))
		len++;
	word = ft_malloc(sizeof(char) * (len + 1));
	if (word == NULL)
		return (NULL);
	word[len] = 0;
	while (--len >= 0)
	{
		word[len] = str[len];
	}
	return (word);
}

static char	**cancel(char **words, size_t nb_words)
{
	size_t	i;

	i = 0;
	while (i < nb_words)
		ft_free(words[i++]);
	ft_free(words);
	return (NULL);
}

char	**ft_split_white(char const *s)
{
	size_t	i;
	size_t	nb_words;
	char	**words;

	if (s == NULL)
		return (NULL);
	nb_words = get_nb_words(s);
	words = ft_malloc(sizeof(char *) * (nb_words + 1));
	if (words == NULL)
		return (NULL);
	words[nb_words] = 0;
	i = 0;
	while (i < nb_words)
	{
		if (ft_isspace(*s))
			s = skip(s);
		words[i] = dup_until_sep(s);
		if (words[i] == NULL)
			return (cancel(words, i));
		s = skip(s);
		i++;
	}
	return (words);
}

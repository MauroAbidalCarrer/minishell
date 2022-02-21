/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 21:24:55 by maabidal          #+#    #+#             */
/*   Updated: 2021/12/16 18:58:27 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static char	*skip(const char *str, char sep)
{
	size_t	i;

	i = 0;
	while (str[i] && (*str == sep) == (str[i] == sep))
		i++;
	return ((char *)str + i);
}

static int	get_nb_words(const char *str, char c)
{
	size_t	nb;
	int		i;

	i = 0;
	nb = (*str && *str != c);
	while (str[i] && str[i + 1])
	{
		nb += (str[i] == c && str[i + 1] != c);
		i++;
	}
	return (nb);
}

static char	*dup_until_sep(char const*str, char sep)
{
	ssize_t	len;
	char	*word;

	len = 0;
	while (str[len] && str[len] != sep)
		len++;
	word = malloc(sizeof(char) * (len + 1));
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
		free(words[i++]);
	free(words);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	nb_words;
	char	**words;

	if (s == NULL)
		return (NULL);
	nb_words = get_nb_words(s, c);
	words = malloc(sizeof(char *) * (nb_words + 1));
	if (words == NULL)
		return (NULL);
	words[nb_words] = 0;
	i = 0;
	while (i < nb_words)
	{
		if (*s == c)
			s = skip(s, c);
		words[i] = dup_until_sep(s, c);
		if (words[i] == NULL)
			return (cancel(words, i));
		s = skip(s, c);
		i++;
	}
	return (words);
}

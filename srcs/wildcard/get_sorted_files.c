/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sorted_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 15:22:13 by jmaia             #+#    #+#             */
/*   Updated: 2022/03/11 15:48:17 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

static int	ft_nosensitive_strcmp(void *a, void *b);
static int	ft_nosensitive_strncmp(char *s1, char *s2, size_t n);

t_list	*get_sorted_files(DIR *dir)
{
	struct dirent	*dirent;
	t_list			*lst;
	t_list			*cur;

	errno = 0;
	lst = 0;
	dirent = readdir(dir);
	while (dirent)
	{
		cur = ft_lstnew(ft_strdup(dirent->d_name));
		if (!cur || !cur->content)
			break ;
		ft_lstadd_back(&lst, cur);
		dirent = readdir(dir);
	}
	ft_lstsort(lst, (int (*)(void *, void *))(&ft_nosensitive_strcmp));
	if (errno)
		ft_lstclear(&lst, &free);
	return (lst);
}

static int	ft_nosensitive_strcmp(void *a, void *b)
{
	char	*s1;
	char	*s2;
	size_t	l1;
	size_t	l2;

	s1 = (char *) a;
	s2 = (char *) b;
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	if (l1 < l2)
		return (ft_nosensitive_strncmp(s1, s2, l2 + 1));
	else
		return (ft_nosensitive_strncmp(s1, s2, l1 + 1));
}

static int	ft_nosensitive_strncmp(char *s1, char *s2, size_t n)
{
	while (n > 0 && *s1 && *s2)
	{
		if (ft_tolower(*s1) != ft_tolower(*s2))
			break ;
		s1++;
		s2++;
		n--;
	}
	if (ft_tolower(*s1) != ft_tolower(*s2) && n)
		return ((unsigned char)ft_tolower(*s1)
			- (unsigned char)ft_tolower(*s2));
	return (0);
}

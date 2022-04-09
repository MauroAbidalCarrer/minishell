/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:01:52 by jmaia             #+#    #+#             */
/*   Updated: 2021/12/02 10:51:53 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strdup_or_null_if_empty(char *s)
{
	char			*dup;
	unsigned int	i;
	size_t			len_s;

	if (*s == 0)
		return (0);
	len_s = 0;
	i = 0;
	while (s[i++])
		len_s++;
	dup = malloc(sizeof(*dup) * (len_s + 1));
	if (dup == 0)
		return (0);
	i = 0;
	while (i < sizeof(*dup) * (len_s + 1))
	{
		dup[i] = s[i];
		i++;
	}
	return (dup);
}

static t_file	init_file(int fd)
{
	t_file	file;

	file.fd = fd;
	file.i = BUFFER_SIZE;
	file.real_size = BUFFER_SIZE;
	file.is_end = 0;
	return (file);
}

t_file	*get_file(t_infinite_tab *files, int fd)
{
	unsigned int	i;
	t_file			file;

	if (files->tab == 0)
	{
		files->i = 0;
		files->size = 0;
		files->elem_size = sizeof(t_file);
		files->tab = malloc(sizeof(*files->tab) * files->elem_size);
		if (files->tab == 0)
			return (0);
		((t_file *) &files->tab[0])->fd = -2;
		files->count = 0;
	}
	i = 0;
	while (((t_file *) &files->tab[i * files->elem_size])->fd != -2)
	{
		if (((t_file *) &files->tab[i * files->elem_size])->fd == fd)
			return ((t_file *) &files->tab[i * files->elem_size]);
		i++;
	}
	file = init_file(fd);
	append_elem(files, &file + 0 * files->count++);
	((t_file *)(&files->tab[files->i * files->elem_size]))->fd = -2;
	return ((t_file *) &files->tab[i * files->elem_size]);
}

static void	free_infinite_tab(t_infinite_tab *tab, t_infinite_tab *files)
{
	free(tab->tab);
	free(tab);
	if (files->count == 0)
	{
		free(files->tab);
		files->tab = 0;
	}
}

char	*get_next_line(int fd)
{
	static t_infinite_tab	files = {.tab = 0};
	t_backpack				backpack;

	backpack = get_backpack(&files, fd);
	if (backpack.is_bad_backpack)
		return (0);
	while (!backpack.c->is_end && backpack.c->c != '\n')
	{
		free(backpack.c);
		backpack.c = get_next_char(backpack.file, &files);
		if (backpack.c->is_end)
			continue ;
		backpack.err = append_elem(backpack.line, &backpack.c->c);
		if (backpack.err == e_err)
		{
			free(backpack.c);
			free_infinite_tab(backpack.line, &files);
			return (0);
		}
	}
	free(backpack.c);
	backpack.return_line = ft_strdup_or_null_if_empty(backpack.line->tab);
	free_infinite_tab(backpack.line, &files);
	return (backpack.return_line);
}

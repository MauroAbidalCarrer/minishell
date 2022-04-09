/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:54:08 by jmaia             #+#    #+#             */
/*   Updated: 2021/12/02 10:52:31 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_char_file	*get_next_char(t_file	*file, t_infinite_tab *files)
{
	t_char_file	*c_file;

	c_file = malloc(sizeof(*c_file));
	if (!c_file)
		return (0);
	if (file->is_end)
	{
		file->fd = -1;
		c_file->is_end = 1;
		files->count--;
		return (c_file);
	}
	if (file->i == file->real_size)
	{
		file->real_size = read(file->fd, file->buffer, BUFFER_SIZE);
		if (file->real_size == 0 || file->real_size == -1)
			file->is_end = 1;
		else
			file->i = 0;
		free(c_file);
		return (get_next_char(file, files));
	}
	c_file->is_end = 0;
	c_file->c = file->buffer[file->i++];
	return (c_file);
}

t_infinite_tab	*init_infinite_tab(unsigned int elem_size)
{
	t_infinite_tab	*tab;

	tab = malloc(sizeof(*tab));
	if (tab == 0)
		return (0);
	tab->tab = malloc(elem_size * DEFAULT_INF_STR_SIZE);
	if (tab->tab == 0)
	{
		free(tab);
		return (0);
	}
	tab->i = 0;
	tab->size = DEFAULT_INF_STR_SIZE;
	tab->elem_size = elem_size;
	return (tab);
}

enum e_error	extend_infinite_tab(t_infinite_tab *tab)
{
	unsigned int	new_size;
	char			*extended_tab;
	size_t			i;

	new_size = tab->size + DEFAULT_INF_STR_SIZE;
	extended_tab = malloc(tab->elem_size * new_size);
	if (extended_tab == 0)
		return (e_err);
	i = 0;
	while (i < tab->elem_size * tab->size)
	{
		extended_tab[i] = tab->tab[i];
		i++;
	}
	tab->size = new_size;
	free(tab->tab);
	tab->tab = extended_tab;
	return (e_ok);
}

enum e_error	append_elem(t_infinite_tab *tab, void *elem)
{
	unsigned int	i;
	char			*bytes;
	enum e_error	err;

	if (tab->i + 1 >= tab->size)
	{
		err = extend_infinite_tab(tab);
		if (err == e_err)
			return (e_err);
		return (append_elem(tab, elem));
	}
	i = 0;
	bytes = (char *) elem;
	while (i < tab->elem_size)
	{
		tab->tab[tab->i * tab->elem_size + i] = bytes[i];
		tab->tab[(tab->i + 1) * tab->elem_size + i] = 0;
		i++;
	}
	tab->i++;
	return (e_ok);
}

t_backpack	get_backpack(t_infinite_tab *files, int fd)
{
	t_backpack	backpack;

	backpack.is_bad_backpack = 1;
	backpack.c = malloc(sizeof(*backpack.c));
	if (!backpack.c)
		return (backpack);
	backpack.line = init_infinite_tab(sizeof(char));
	if (!backpack.line)
	{
		free(backpack.c);
		return (backpack);
	}
	backpack.line->tab[0] = 0;
	backpack.c->c = 0;
	backpack.c->is_end = 0;
	backpack.file = get_file(files, fd);
	if (!backpack.file)
	{
		free(backpack.c);
		free(backpack.line);
	}
	backpack.is_bad_backpack = 0;
	return (backpack);
}

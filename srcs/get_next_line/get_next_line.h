/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 11:57:54 by jmaia             #+#    #+#             */
/*   Updated: 2022/04/09 09:28:42 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# define DEFAULT_INF_STR_SIZE 50
# define BUFFER_SIZE 50

enum e_error { e_ok, e_err };

typedef struct s_file
{
	int				fd;
	unsigned int	i;
	char			buffer[BUFFER_SIZE];
	ssize_t			real_size;
	int				is_end;
}	t_file;

typedef struct s_infinite_tab
{
	char			*tab;
	unsigned int	i;
	unsigned int	size;
	unsigned int	elem_size;
	unsigned int	count;
}	t_infinite_tab;

typedef struct s_char_file
{
	char	c;
	int		is_end;
}	t_char_file;

typedef struct s_backpack
{
	t_infinite_tab		*line;
	char				*return_line;
	t_char_file			*c;
	enum e_error		err;
	t_file				*file;
	int					is_bad_backpack;

}	t_backpack;

char			*get_next_line(int fd);
t_char_file		*get_next_char(t_file *file, t_infinite_tab *files);
t_infinite_tab	*init_infinite_tab(unsigned int elem_size);
void			*ft_memcpy(void *dest, const void *src, size_t n);
enum e_error	append_elem(t_infinite_tab *tab, void *elem);
t_backpack		get_backpack(t_infinite_tab *files, int fd);
t_file			*get_file(t_infinite_tab *files, int fd);

char			*get_next_line_heredoc(void);

#endif

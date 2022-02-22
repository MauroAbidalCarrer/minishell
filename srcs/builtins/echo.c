/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:12:31 by jmaia             #+#    #+#             */
/*   Updated: 2022/02/22 19:53:47 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static size_t	get_args_size(int ac, char **av);
static int		has_new_line(int ac, char **av);
static void		append_args_to(char *msg, int ac, char **av);
static void		append_newline_if_needed_to(char *msg, int ac, char **av);

/* NEED TO BE DELETED */
int				ft_write(int fd, const char *buf, size_t count);
void			ft_free(void *ptr);
void			*ft_malloc(size_t size);
size_t			ft_strlen(const char *str);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			ft_memcpy(char *dest, const char *src, size_t n);

int	ms_echo(int ac, char **av)
{
	char	*msg;
	int		err;
	size_t	msg_len;

	msg_len = get_args_size(ac, av) + has_new_line(ac, av) + 1;
	msg = ft_malloc(sizeof(*msg) * msg_len);
	if (!msg)
		return (1);
	append_args_to(msg, ac, av);
	append_newline_if_needed_to(msg, ac, av);
	err = ft_write(1, msg, get_args_size(ac, av));
	ft_free(msg);
	return (err);
}

static size_t	get_args_size(int ac, char **av)
{
	int		i;
	size_t	size;

	i = 1 + has_new_line(ac, av);
	size = 0;
	while (i < ac)
	{
		size += ft_strlen(av[i]);
		i++;
	}
	return (size);
}

static int	has_new_line(int ac, char **av)
{
	return (ac >= 2 && ft_strncmp(av[1], "-n", ft_strlen(av[1])));
}

static void	append_args_to(char *msg, int ac, char **av)
{
	int	i;
	int	i_msg;

	i = 1;
	i_msg = 0;
	while (i < ac)
	{
		ft_memcpy(msg + i_msg, av[i], ft_strlen(av[i]));
		i_msg += ft_strlen(av[i]);
		msg[++i_msg] = ' ';
		i++;
	}
	msg[i_msg] = 0;
}

static void	append_newline_if_needed_to(char *msg, int ac, char **av)
{
	int	i;

	if (!has_new_line(ac, av))
		return ;
	i = 0;
	while (msg[i])
		i++;
	msg[i] = '\n';
	msg[i + 1] = 0;
}

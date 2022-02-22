/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:12:31 by jmaia             #+#    #+#             */
/*   Updated: 2022/02/22 21:44:26 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static size_t	get_args_size(int ac, char **av);
static int		has_new_line(int ac, char **av);
static void		append_args_to(char *msg, int ac, char **av);
static void		append_newline_if_needed_to(char *msg, int ac, char **av);

int	ms_echo(int ac, char **av)
{
	char	*msg;
	int		err;
	size_t	msg_len;

	if (ac == 2 && !ft_strcmp(av[1], "-n"))
		return (ft_write(1, "\n", 1));
	msg_len = get_args_size(ac, av) + has_new_line(ac, av) + 1;
	msg = ft_malloc(sizeof(*msg) * msg_len);
	if (!msg)
		return (1);
	msg[0] = 0;
	append_args_to(msg, ac, av);
	append_newline_if_needed_to(msg, ac, av);
	err = ft_write(1, msg, ft_strlen(msg));
	ft_free(msg);
	return (err);
}

static size_t	get_args_size(int ac, char **av)
{
	int		i;
	size_t	size;

	size = 0;
	i = 1 + !has_new_line(ac, av);
	if (i >= ac)
		return (0);
	while (i < ac)
	{
		size += ft_strlen(av[i]);
		i++;
	}
	size += ac - 1 - !has_new_line(ac, av) - 1;
	return (size);
}

static int	has_new_line(int ac, char **av)
{
	return (ac < 2 || ft_strcmp(av[1], "-n"));
}

static void	append_args_to(char *msg, int ac, char **av)
{
	int	i;
	int	i_msg;

	i = 1 + !has_new_line(ac, av);
	i_msg = 0;
	while (i < ac)
	{
		ft_memcpy(msg + i_msg, av[i], ft_strlen(av[i]));
		i_msg += ft_strlen(av[i]);
		msg[i_msg++] = ' ';
		i++;
	}
	if (i > 1 + !has_new_line(ac, av))
		msg[i_msg - 1] = 0;
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

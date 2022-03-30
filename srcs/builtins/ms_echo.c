/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:12:31 by jmaia             #+#    #+#             */
/*   Updated: 2022/03/30 14:23:47 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static size_t	get_args_size(int ac, char **av);
static int		count_nl_options(int ac, char **av);
static void		append_args_to(char *msg, int ac, char **av);
static void		append_newline_if_needed_to(char *msg, int ac, char **av);

int	ms_echo(int ac, char **av, t_env env)
{
	char	*msg;
	int		err;
	size_t	msg_len;

	(void) env;
	msg_len = get_args_size(ac, av) + !count_nl_options(ac, av) + 1;
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
	i = 1 + count_nl_options(ac, av);
	if (i >= ac)
		return (0);
	while (i < ac)
	{
		size += ft_strlen(av[i]);
		i++;
	}
	size += ac - 1 - count_nl_options(ac, av) - 1;
	return (size);
}

static int	count_nl_options(int ac, char **av)
{
	int	i;
	int	j;
	int	count;

	if (ac < 2 || av[1][0] != '-')
		return (0);
	j = 1;
	count = 0;
	while (j < ac)
	{
		if (av[j][0] != '-')
			return (count);
		i = 1;
		while (av[j][i])
		{
			if (av[j][i] != 'n')
				return (count);
			i++;
		}
		j++;
		count++;
	}
	return (count);
}

static void	append_args_to(char *msg, int ac, char **av)
{
	int	i;
	int	i_msg;

	i = 1 + count_nl_options(ac, av);
	i_msg = 0;
	while (i < ac)
	{
		ft_memcpy(msg + i_msg, av[i], ft_strlen(av[i]));
		i_msg += ft_strlen(av[i]);
		msg[i_msg++] = ' ';
		i++;
	}
	if (i > 1 + count_nl_options(ac, av))
		msg[i_msg - 1] = 0;
}

static void	append_newline_if_needed_to(char *msg, int ac, char **av)
{
	int	i;

	if (count_nl_options(ac, av))
		return ;
	i = 0;
	while (msg[i])
		i++;
	msg[i] = '\n';
	msg[i + 1] = 0;
}

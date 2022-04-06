/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:48:39 by jmaia             #+#    #+#             */
/*   Updated: 2022/04/06 15:54:33 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	is_long(char *nbr);

int	ms_exit(int ac, char **av, t_env env)
{
	char	*err_msg;

	(void) env;
	if (isatty(0))
		ft_write(2, "exit\n", 5);
	if (ac == 1)
		ft_exit(env.exit_status);
	if (!ft_isnbr(av[1]) || !is_long(av[1]))
	{
		err_msg = ft_malloc(sizeof(char) * (28 + ft_strlen(av[1])));
		ft_memcpy(err_msg, av[1], ft_strlen(av[1]));
		ft_memcpy(err_msg + ft_strlen(av[1]),
			": numeric argument required", 27);
		err_msg[27 + ft_strlen(av[1])] = 0;
		write_error(NULL, "exit", err_msg);
		ft_free(err_msg);
		ft_exit(2);
	}
	if (ac > 2)
	{
		write_error(NULL, "exit", "too many arguments");
		return (1);
	}
	ft_exit(ft_atoi(av[1]));
	return (1);
}

static int	is_long(char *nbr)
{
	int		i;
	int		n_digits;
	char	*start_nbr;

	i = 0;
	n_digits = 0;
	start_nbr = 0;
	while (nbr[i])
	{
		if (ft_isdigit(nbr[i]))
		{
			if (start_nbr == 0)
				start_nbr = nbr + i;
			n_digits++;
		}
		i++;
	}
	if (n_digits > 19 || ft_strncmp(start_nbr, "9223372036854775808", 19) > 0)
		return (0);
	return (1);
}

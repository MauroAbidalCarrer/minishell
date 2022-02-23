/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:48:39 by jmaia             #+#    #+#             */
/*   Updated: 2022/02/23 16:03:56 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ms_exit(int ac, char **av)
{
	int	err;

	if (ac == 1)
	{
		printf("ALERTE CECI NE DOIT JAMAIS S'AFFICHER,GO ETRE SANS GLOBALES\n");
		return (1);
	}
	err = (ft_write(2, "exit\n", 5) == -1);
	if (!ft_isnbr(av[1]))
	{
		err = (ft_write(2, av[0], ft_strlen(av[0])) == -1);
		err = (ft_write(2, ": exit: ", 8) == -1);
		err = (ft_write(2, av[1], ft_strlen(av[1])) == -1);
		err = (ft_write(2, ": numeric argument required\n", 28) == -1);
		ft_exit(2);
	}
	if (ac > 2)
	{
		err = (ft_write(2, av[0], ft_strlen(av[0])) == -1);
		err = (ft_write(2, ": exit: too many arguments\n", 27) == -1);
		return (1);
	}
	ft_exit(ft_atoi(av[1]));
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_write_sys_calls.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 17:20:45 by maabidal          #+#    #+#             */
/*   Updated: 2022/02/22 17:44:39 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
 char	*exe_name;
 t_list	*ptrs_lst;

int	main(int ac, char **av)
{
exe_name = av[0];
	ft_putstr_fd(av[1], -32);
printf("openin(av[1]) = %d\n", open(av[1], O_RDONLY));
printf("printing errror\n");
	write_error(av[1]);
}

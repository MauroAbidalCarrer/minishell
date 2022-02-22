/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_file_sys_calls.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 17:45:57 by maabidal          #+#    #+#             */
/*   Updated: 2022/02/22 18:37:25 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
 char	*exe_name;
 t_list	*ptrs_lst;

int	main(int ac, char **av)
{
exe_name = av[1];
printf("opening av[1] fd\n");
	ft_open((const char *)av[1], 0);
}

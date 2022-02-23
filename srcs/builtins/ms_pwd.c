/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:19:42 by jmaia             #+#    #+#             */
/*   Updated: 2022/02/23 15:40:25 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ms_pwd(int ac, char **av)
{
	char	*pwd;
	char	*err_msg;

	(void) ac;
	pwd = getcwd(0, 0);
	if (!pwd)
	{
		err_msg = strerror(errno);
		ft_write(2, av[0], ft_strlen(av[0]));
		ft_write(2, ": ", 2);
		ft_write(2, err_msg, ft_strlen(err_msg));
		return (1);
	}
	ft_write(1, pwd, ft_strlen(pwd));
	ft_write(1, "\n", 1);
	free(pwd);
	return (0);
}

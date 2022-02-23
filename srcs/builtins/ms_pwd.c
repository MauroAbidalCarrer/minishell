/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:19:42 by jmaia             #+#    #+#             */
/*   Updated: 2022/02/23 15:46:25 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ms_pwd(int ac, char **av)
{
	char	*pwd;
	char	*err_msg;
	int		err;

	(void) ac;
	pwd = getcwd(0, 0);
	if (!pwd)
	{
		err_msg = strerror(errno);
		err = ft_write(2, av[0], ft_strlen(av[0])) == -1;
		err = (!err && ft_write(2, ": ", 2) == -1);
		err = (!err && ft_write(2, err_msg, ft_strlen(err_msg)) == -1);
		return (1);
	}
	err = ft_write(1, pwd, ft_strlen(pwd)) == -1;
	err = (!err && ft_write(1, "\n", 1) == -1);
	free(pwd);
	return (0);
}

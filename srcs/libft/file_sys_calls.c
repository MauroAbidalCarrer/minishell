/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_sys_calls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:32:32 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/10 00:48:18 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_close(int fd)
{
	if (close(fd) == -1)
	{
		write_error(NULL);
		ft_exit(1);
	}
}

int	ft_open(const char *pathname, int flags)
{
	int	fd;

	fd = open(pathname, flags, CREAT_M);
	if (fd == -1)
		write_error((char *)pathname);
	return (fd);
}

void	ft_dup2(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
	{
		write_error(NULL);
		ft_exit(1);
	}
}

void	ft_pipe(int *p_fds)
{
	if (pipe(p_fds) == -1)
	{
		write_error(NULL);
		ft_exit(1);
	}
}

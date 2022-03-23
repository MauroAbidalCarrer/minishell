/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_sys_calls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:32:32 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/23 14:41:15 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_close(int fd)
{
	if (close(fd) == -1)
	{
		write_error(NULL, NULL, NULL);
		ft_exit(1);
	}
}

int	ft_open(const char *pathname, int flags)
{
	int	fd;

	fd = open(pathname, flags, CREAT_M);
	if (fd == -1)
		write_error(NULL, (char *)pathname, NULL);
	return (fd);
}

int	ft_dup(int oldfd)
{
	int	new_fd;

	new_fd = dup(oldfd);
	if (new_fd == -1)
	{
		write_error(NULL, NULL, NULL);
		ft_exit(1);
	}
	return (new_fd);
}

void	ft_dup2(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
	{
		write_error(NULL, NULL, NULL);
		ft_exit(1);
	}
	ft_close(old_fd);
}

void	ft_pipe(int p_fds[2])
{
	if (pipe(p_fds) == -1)
	{
		write_error(NULL, NULL, NULL);
		ft_exit(1);
	}
}

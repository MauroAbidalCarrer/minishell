/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_sys_calls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:32:32 by maabidal          #+#    #+#             */
/*   Updated: 2022/04/05 15:04:23 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_close(int fd)
{
	if (close(fd) == -1)
	{
		write_error(NULL, ft_strjoin("ft_close ", ft_itoa(fd)), NULL);
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
		write_error(NULL, ft_strjoin("ft_dup ", ft_itoa(oldfd)), NULL);
		ft_exit(1);
	}
	return (new_fd);
}

void	ft_dup2(int old_fd, int new_fd)
{
	char	*err_msg;

	if (dup2(old_fd, new_fd) == -1)
	{
		err_msg = ft_strjoin("ft_dup2(", ft_itoa(old_fd));
		err_msg = ft_strjoin(err_msg, ", ");
		err_msg = ft_strjoin(err_msg, ft_itoa(new_fd));
		err_msg = ft_strjoin(err_msg, ")");
		write_error(NULL, err_msg, NULL);
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

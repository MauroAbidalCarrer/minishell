/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_sys_calls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:21:27 by maabidal          #+#    #+#             */
/*   Updated: 2022/02/22 19:47:16 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_write(int fd, const void *buf, size_t count)
{
	int	result;

	result = write(fd, buf, count);
	if (result == -1)
		perror(g_exe_name);
	return (result);
}

void	small_cat(char *src, char *dst)
{
	static int	i;
	int			j;

	j = 0;
	while (src[j])
	{
		dst[i] = src[j];
		j++;
		i++;
	}
	dst[i] = 0;
}

void	write_error(char *app_msg)
{
	char	buff[2048];

	small_cat(g_exe_name, buff);
	if (app_msg)
	{
		small_cat(": ", buff);
		small_cat(app_msg, buff);
	}
	small_cat(": ", buff);
	small_cat(strerror(errno), buff);
	small_cat("\n", buff);
	ft_putstr_fd(buff, 2);
}

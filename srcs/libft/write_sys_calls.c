/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_sys_calls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:21:27 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/11 04:24:04 by maabidal         ###   ########.fr       */
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

int	small_cat(char *src, char *dst, int i)
{
	int	j;

	j = 0;
	while (src[j])
	{
		dst[i] = src[j];
		j++;
		i++;
	}
	dst[i] = 0;
	return (i);
}

void	write_error(char *app_msg)
{
	char	buff[2048];
	int		i;

	i = small_cat(g_exe_name, buff, 0);
	if (app_msg)
	{
		i = small_cat(": ", buff, i);
		i = small_cat(app_msg, buff, i);
	}
	i = small_cat(": ", buff, i);
	i = small_cat(strerror(errno), buff, i);
	i = small_cat("\n", buff, i);
	while (i < 2048)
		buff[i++] = 0;
	ft_putstr_fd(buff, 2);
}

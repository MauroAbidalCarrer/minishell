/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_sys_calls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:21:27 by maabidal          #+#    #+#             */
/*   Updated: 2022/04/06 14:44:56 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_write(int fd, const void *buf, size_t count)
{
	int	result;

	result = write(fd, buf, count);
	if (result == -1 && fd != 2)
		write_error(NULL, NULL, NULL);
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

void	write_error(char *exename, char *subject, char *msg)
{
	static char	*_exename;
	char		buff[2048];
	int			i;

	if (exename)
	{
		_exename = exename;
		return ;
	}
	i = small_cat(_exename, buff, 0);
	if (subject)
	{
		i = small_cat(subject, buff, i);
		i = small_cat(": ", buff, i);
	}
	if (msg)
		i = small_cat(msg, buff, i);
	else
		i = small_cat(strerror(errno), buff, i);
	i = small_cat("\n", buff, i);
	while (i < 2048)
		buff[i++] = 0;
	ft_putstr_fd(buff, 2);
}

/*
void	write_error(char *msg, char *app_msg, char *exename)
{
	static char	*_exename;
	char		buff[2048];
	int			i;

	if (exename)
	{
		_exename = exename;
		return ;
	}
	i = small_cat(_exename, buff, 0);
	if (app_msg)
	{
		i = small_cat(app_msg, buff, i);
		i = small_cat(": ", buff, i);
	}
	i = small_cat(strerror(errno), buff, i);
	i = small_cat("\n", buff, i);
	while (i < 2048)
		buff[i++] = 0;
	ft_putstr_fd(buff, 2);
}
*/

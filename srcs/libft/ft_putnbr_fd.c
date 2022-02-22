/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 20:03:55 by maabidal          #+#    #+#             */
/*   Updated: 2021/12/13 20:04:17 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static void	putdigit(long n, int fd)
{
	if (n >= 10)
		putdigit(n / 10, fd);
	ft_putchar_fd('0' + n % 10, fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		putdigit(-((long)n), fd);
	}
	else
		putdigit((long)n, fd);
}

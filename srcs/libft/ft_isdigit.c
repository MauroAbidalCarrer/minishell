/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 19:59:38 by maabidal          #+#    #+#             */
/*   Updated: 2021/12/13 20:15:25 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	inrange(int c, char a, char b)
{
	return (c >= (unsigned char)a && c <= (unsigned char)b);
}

int	ft_isdigit(int c)
{
	return (inrange(c, '0', '9'));
}

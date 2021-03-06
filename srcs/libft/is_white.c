/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_white.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 00:35:47 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/06 00:44:32 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	inrange(char c, char a, char b)
{
	return (c >= a && c <= b);
}

int	is_white(char c)
{
	return (c == ' ' || inrange(c, 9, 13));
}

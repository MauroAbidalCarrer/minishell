/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:22:33 by maabidal          #+#    #+#             */
/*   Updated: 2022/02/22 18:48:57 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*skip(char *str, char c)
{
	while (*str == c && *str)
		str++;
	return (str);
}

int	str_is_valid_list(char *str)
{
	str = skip(str , ' ');
}

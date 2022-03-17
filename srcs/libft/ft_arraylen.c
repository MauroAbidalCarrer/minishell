/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraylen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 13:04:03 by jmaia             #+#    #+#             */
/*   Updated: 2022/03/17 13:07:38 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_arraylen(void **array)
{
	size_t	size;

	if (!array)
		return (0);
	size = 0;
	while (array[size])
		size++;
	return (size);
}

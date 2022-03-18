/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_convert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 11:22:25 by jmaia             #+#    #+#             */
/*   Updated: 2021/12/06 17:38:38 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer_convert.h"

char	*as_str(t_dynamic_buffer *buffer)
{
	char	*str;
	size_t	len;

	len = buffer->elem_size * buffer->i;
	str = malloc(sizeof(*str) * (len + 1));
	if (!str)
		return (0);
	ft_memcpy(str, buffer->buffer, sizeof(*str) * len);
	str[len] = 0;
	return (str);
}

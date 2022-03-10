/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_buffer.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 11:09:40 by jmaia             #+#    #+#             */
/*   Updated: 2021/12/03 11:17:13 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DYNAMIC_BUFFER_H
# define DYNAMIC_BUFFER_H
# define EXPAND_LEN 10
# include <stdlib.h>

# include "libft.h"
# include "libdynamic_buffer.h"

static void			*get_elem_ptr(t_dynamic_buffer *buffer, unsigned long i);
static int			expand(t_dynamic_buffer *buffer);
#endif

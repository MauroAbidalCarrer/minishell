/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:57:02 by jmaia             #+#    #+#             */
/*   Updated: 2022/04/04 17:59:05 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*get_msg_err(char *arg)
{
	char	*err_msg;

	err_msg = ft_malloc(sizeof(char) * (ft_strlen(arg) + 27));
	err_msg[0] = '`';
	ft_memcpy(err_msg + 1, arg, ft_strlen(arg));
	err_msg[ft_strlen(arg) + 1] = '\'';
	ft_memcpy(err_msg + ft_strlen(arg) + 2, ": not a valid identifier", 24);
	err_msg[ft_strlen(arg) + 26] = 0;
	return (err_msg);
}

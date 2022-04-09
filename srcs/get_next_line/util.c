/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:35:52 by maabidal          #+#    #+#             */
/*   Updated: 2022/04/09 09:28:11 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

char	*get_next_line_heredoc(void)
{
	char	*tmp;

	ft_putstr_fd("> ", 1);
	tmp = get_next_line(0);
	if (tmp && ft_strlen(tmp) && tmp[ft_strlen(tmp) - 1] == '\n')
		tmp[ft_strlen(tmp) - 1] = 0;
	return (tmp);
}

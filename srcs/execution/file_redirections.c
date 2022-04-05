/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:41:24 by maabidal          #+#    #+#             */
/*   Updated: 2022/04/04 21:38:08 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	fredi(char *arg, int flags, int stream)
{
	int		fd;

	fd = ft_open(arg, flags);
	if (fd == -1)
		return (1);
	ft_dup2(fd, stream);
	return (0);
}

int	apply_infile(char *cmd_s, char **last_if)
{
	while (strchr_q(cmd_s, '<'))
	{
		cmd_s = strchr_q(cmd_s, '<') + 1;
		if (*cmd_s == '<')
		{
			cmd_s++;
			continue ;
		}
		*last_if = cmd_s - 1;
		if (fredi(sub_argument(cmd_s), READ_F, READ))
			return (1);
		cmd_s = skip_argument(cmd_s);
	}
	return (0);
}

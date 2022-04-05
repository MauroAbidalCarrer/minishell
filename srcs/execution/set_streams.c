/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:41:24 by maabidal          #+#    #+#             */
/*   Updated: 2022/04/05 19:51:57 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	fredi(char *arg, int flags, int stream)
{
	int		fd;

	fd = ft_open(arg, flags);
	if (fd == -1)
		return (1);
	ft_dup2(fd, stream);
	return (0);
}

static int	in_fredi(char *cmd_s, int **r_pipes, int is_child)
{
	if (*cmd_s == '<')
	{
		ft_dup2(**r_pipes, READ);
		(*r_pipes)++;
		return (0);
	}
	return (fredi(cmd_s, READ_F, READ));
}

static int out_fredi(char *cmd_s)
{
	if (*cmd_s == '>')
	{
		cmd_s++;
		return (fredi(sub_argument(cmd_s), APPEND_F, WRITE));
	}
	return (fredi(sub_argument(cmd_s), CREAT_F, WRITE));
}

static void	close_rest_of_r_pipes(int **r_pipes, int is_child)
{
	while (is_child &&**r_pipes != -1)
	{
		ft_close(**r_pipes);
		(*r_pipes)++;
	}
}

int	set_streams(char *cmd_s, int **r_pipes, int is_child)
{
	char	*next_in;
	char	*next_out;

	while (1)
	{
		next_in = strch_q(cmd_s, '<');
		next_out = strch_q(cmd_s, '>');
		if (next_in && (!next_out || next_in < next_out))
		{
			str = next_in + 1;
			if (in_fredi(cmd_s, r_pipes, is_child, ret))
				return (1);
		}
		else if (next_out)
		{
			str = next_out + 1;
			if (out_fredi(cmd_s))
				return (1);
		}
		else
			break ;
		str += (*str == '<' || *str == '>');
	}
	close_rest_of_r_pipes(r_pipes, is_child);
	return(0);
}

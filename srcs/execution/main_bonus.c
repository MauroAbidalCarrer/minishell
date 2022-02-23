/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 18:47:32 by maabidal          #+#    #+#             */
/*   Updated: 2022/02/11 21:29:12 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	here_doc(int fd, char *limit)
{
	char	*line;
	char	tmp;

	while (1)
	{
		write(OUT, "heredoc> ", 9);
		line = get_next_line(IN);
		if (!line)
			break ;
		tmp = line[index_of(0, limit, 0)];
		if (tmp == '\n')
			line[index_of(0, limit, 0)] = 0;
		if (is_str(line, limit))
			break ;
		line[index_of(0, limit, 0)] = tmp;
		write(fd, line, index_of(0, line, 0));
	}
	ft_close(fd);
}

int	exe_mid_cmds(int nb_cmds, char **av, char **env, int c_read_p)
{
	int	p_fds2[2];

	while (nb_cmds--)
	{
		ft_pipe(p_fds2);
		if (ft_fork() == 0)
		{
			ft_close(p_fds2[0]);
			exe_pipe(*av, env, c_read_p, p_fds2[1]);
		}
		ft_close(p_fds2[1]);
		ft_close(c_read_p);
		c_read_p = p_fds2[0];
		av++;
	}
	return (c_read_p);
}

void	exe_cmds_hd(int ac, char **av, char **env, int read_pipe)
{
	int	p_fds2[2];
	int	p_read_n_open_f[2];

	ft_pipe(p_fds2);
	if (ft_fork() == 0)
	{
		ft_close(p_fds2[0]);
		exe_pipe(*av, env, read_pipe, p_fds2[1]);
	}
	ft_close(p_fds2[1]);
	ft_close(read_pipe);
	read_pipe = exe_mid_cmds(ac - 3, av + 1, env, p_fds2[0]);
	p_read_n_open_f[0] = read_pipe;
	p_read_n_open_f[1] = APPEND_F;
	exe_last(av[ac - 2], av[ac - 1], env, p_read_n_open_f);
}

void	exe_cmds_no_hd(int ac, char **av, char **env, int *p_fds)
{
	int	p_read_n_open_f[2];
	int	fd;

	fd = ft_open(av[0], O_RDONLY, NULL);
	if (ft_fork() == 0)
	{
		ft_close(p_fds[0]);
		exe_first(av[1], fd, env, p_fds[1]);
	}
	ft_close(p_fds[1]);
	ft_close(fd);
	p_fds[0] = exe_mid_cmds(ac - 4, av + 2, env, p_fds[0]);
	p_read_n_open_f[0] = p_fds[0];
	p_read_n_open_f[1] = CREAT_F;
	exe_last(av[ac - 2], av[ac - 1], env, p_read_n_open_f);
}

int	main(int ac, char **av, char **env)
{
	int	hd;
	int	p_fds[2];

	if (ac < 5)
	{
		write(2, "nb of args incorrect, write at least 4 args\n", 43);
		return (1);
	}
	pipe(p_fds);
	hd = is_str("here_doc", av[1]);
	if (hd)
		here_doc(p_fds[1], av[2]);
	av += 1 + hd * 2;
	ac -= 1 + hd * 2;
	if (hd)
		exe_cmds_hd(ac, av, env, p_fds[0]);
	else
		exe_cmds_no_hd(ac, av, env, p_fds);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:15:17 by maabidal          #+#    #+#             */
/*   Updated: 2022/04/09 20:22:36 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

//gerer EOF
static void	heredoc(char *limit, char *full_limiter, int p_write, t_env env)
{
	char	*line;
	char	*expanded_line;

	line = get_next_line_heredoc();
	while (line != NULL)
	{
		if (str_equal(line, limit))
			return (free(line));
		if (!strchr(full_limiter, '\"') && !strchr(full_limiter, '\"'))
		{
			expanded_line = var_expand_in_heredoc(line, env);
			free(line);
			line = expanded_line;
		}
		ft_putstr_fd(ft_strjoin(line, "\n"), p_write);
		if (strchr(full_limiter, '\"') || strchr(full_limiter, '\"'))
			free(line);
		line = get_next_line_heredoc();
	}
	write_error(NULL, EOF_WARN, ft_strjoin(limit, EOF_WARN_END));
}

static void	fill_heredocs(char *list, int **pipes, t_env env)
{
	char	*full_limiter;

	set_signal_handler(&handle_sig_as_heredoc);
	while (strstr_q(list, "<<"))
	{
		list = strstr_q(list, "<<") + 2;
		list = skip_spaces(list);
		full_limiter = sub(list, skip_argument(list));
		heredoc(sub_argument(list), full_limiter, pipes[0][WRITE], env);
		ft_free(full_limiter);
		ft_close_p(*pipes);
		ft_free(*pipes);
		pipes++;
	}
	ft_exit(0);
}

static int	*get_read_pipes(int **pipes)
{
	int	*r_pipes;
	int	nb_heredocs;

	nb_heredocs = 0;
	while (pipes[nb_heredocs])
		nb_heredocs++;
	r_pipes = ft_malloc(sizeof(int) * (nb_heredocs + 1));
	r_pipes[nb_heredocs] = -1;
	while (--nb_heredocs >= 0)
	{
		ft_close(pipes[nb_heredocs][WRITE]);
		r_pipes[nb_heredocs] = pipes[nb_heredocs][READ];
	}
	return (r_pipes);
}

int	**mk_pipes(char *list)
{
	int	**pipes;
	int	nb_p;

	nb_p = 0;
	while (strstr_q(list, "<<"))
	{
		list = strstr_q(list, "<<") + 2;
		nb_p++;
	}
	pipes = ft_malloc(sizeof(int *) * (nb_p + 1));
	pipes[nb_p] = NULL;
	while (--nb_p >= 0)
	{
		pipes[nb_p] = ft_malloc(sizeof(int) * 2);
		ft_pipe(pipes[nb_p]);
	}
	return (pipes);
}

int	*mk_heredocs(char *list, t_env env)
{
	int		**pipes;
	int		pid;

	pipes = mk_pipes(list);
	pid = ft_fork();
	if (!pid)
		fill_heredocs(list, pipes, env);
	if (ms_waitpid(pid))
	{
		while (*pipes)
		{
			ft_close_p(*pipes);
			ft_free(*pipes);
			pipes++;
		}
		return (NULL);
	}
	return (get_read_pipes(pipes));
}

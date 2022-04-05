/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   high_level.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 11:41:43 by maabidal          #+#    #+#             */
/*   Updated: 2022/04/05 16:25:45 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	**hd_offs(char *beg_list, char *end_list, int **r_pipes)
{
	char	*sub_list;

	sub_list = sub(beg_list, end_list);
	while (strstr_q(sub_list, "<<"))
	{
		sub_list = strstr_q(sub_list, "<<") + 2;
		ft_close(**r_pipes);
		(*r_pipes)++;
	}
	return (r_pipes);
}

static int	exe_pipes(t_p_data data, t_env env, int **r_pipes);

static int	parent_pipe(t_p_data data, char *next_p, t_env env, int **r_pipes)
{
	int	ret;

	if (data.p_read != -1)
		ft_close(data.p_read);
	data.p_read = data.p_fds[READ];
	if (data.p_fds[WRITE] != -1)
		ft_close(data.p_fds[WRITE]);
	if (next_p)
	{
		data.line = next_p;
		ret = exe_pipes(data, env, r_pipes);
		ms_waitpid(data.pid);
		return (ret);
	}
	else
		return (ms_waitpid(data.pid));
}

static int	exe_pipes(t_p_data data, t_env env, int **r_pipes)
{
	char	*next_p;

	next_p = strchr_qp(data.line, '|');
	if (next_p)
	{
		next_p++;
		ft_pipe(data.p_fds);
	}
	else
	{
		data.p_fds[0] = -1;
		data.p_fds[1] = -1;
	}
	data.pid = ft_fork();
	if (data.pid)
		return (parent_pipe(data, next_p, env, hd_offs(data.line, next_p, r_pipes)));
	if (next_p)
		data.line = sub(data.line, next_p - 1);
	if (data.p_fds[READ] != -1)
		ft_close(data.p_fds[READ]);
	if (data.p_fds[WRITE] != -1)
		ft_dup2(data.p_fds[WRITE], WRITE);
	if (data.p_read != -1)
		ft_dup2(data.p_read, READ);
	return (ft_exit(exe_cmd_s(data.line, 1, env, r_pipes)), 1);
}

static int	exe_pipeline(char *line, int is_child, t_env env, int **r_pipes)
{
	t_p_data	data;

	data.line = line;
	data.is_child = is_child;
	data.p_read = -1;
	if (strchr_qp(line, '|'))
		return (exe_pipes(data, env, r_pipes));
	return (exe_cmd_s(line, is_child, env, r_pipes));
}

int	exe_list(char *list, int is_child, t_env env, int **r_pipes)
{
	char	*next_and;
	char	*next_or;
	char	*end;
	int		ret;

	next_and = strstr_qp(list, "&&");
	next_or = strstr_qp(list, "||");
	end = list + ft_strlen(list);
	if ((!next_or && next_and) || (next_and && next_and < next_or))
	{
		ret = exe_pipeline(sub(list, next_and), 0, env, r_pipes);
		if (!ret)
			return (exe_list(sub(next_and + 2, end), 0, env, hd_offs(list, next_and, r_pipes)));
		return (ret);
	}
	else if ((next_or && !next_and) || (next_or && next_and > next_or))
	{
		ret = exe_pipeline(sub(list, next_or), 0, env, r_pipes);
		if (ret)
			return (exe_list(sub(next_or + 2, end), 0, env, hd_offs(list, next_and, r_pipes)));
		return (0);
	}
	return (exe_pipeline(list, is_child, env, r_pipes));
}

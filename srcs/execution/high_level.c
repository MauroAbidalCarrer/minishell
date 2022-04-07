/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   high_level.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 11:41:43 by maabidal          #+#    #+#             */
/*   Updated: 2022/04/07 19:43:52 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	**skip_hds(char *beg_list, char *end_list, int **r_pipes)
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

	r_pipes = skip_hds(data.line, next_p, r_pipes);
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

	next_p = strchr_qp(data.line, '|') + (strchr_qp(data.line, '|') != NULL);
	if (next_p)
		ft_pipe(data.p_fds);
	else
	{
		data.p_fds[0] = -1;
		data.p_fds[1] = -1;
	}
	data.pid = ft_fork();
	if (!data.pid)
	{
		if (next_p)
			data.line = sub(data.line, next_p - 1);
		if (data.p_fds[READ] != -1)
			ft_close(data.p_fds[READ]);
		if (data.p_fds[WRITE] != -1)
			ft_dup2(data.p_fds[WRITE], WRITE);
		if (data.p_read != -1)
			ft_dup2(data.p_read, READ);
		ft_exit(exe_cmd_s(data.line, 1, env, r_pipes));
	}
	return (parent_pipe(data, next_p, env, r_pipes));
}

static int	exe_pipeline(char *line, int is_child, t_env env, int **r_pipes)
{
	t_p_data	data;
	int			ret;

	data.line = line;
	data.is_child = is_child;
	data.p_read = -1;
	if (strchr_qp(line, '|'))
		return (exe_pipes(data, env, r_pipes));
	ret = exe_cmd_s(line, is_child, env, r_pipes);
	skip_hds(line, line + ft_strlen(line) - 1, r_pipes);
	return (ret);
}

int	exe_list(char *list, int is_child, t_env env, int **r_pipes)
{
	int		ret;
	char	*next_op;
	char	*nextnext_op;

	next_op = strstr_qp(list, "||");
	if (strstr_qp(list, "&&") != NULL
		&& (next_op == NULL || strstr_qp(list, "&&") < next_op))
		next_op = strstr_qp(list, "&&");
	if (next_op)
	{
		ret = exe_pipeline(sub(list, next_op), is_child, env, r_pipes);
		if ((ret != 0) == (*next_op == '|'))
			return (exe_list(next_op + 2, is_child, env, r_pipes));
		nextnext_op = tern(*next_op == '|', "&&", "||");
		if (strstr_qp(next_op + 2, nextnext_op))
		{
			nextnext_op = strstr_qp(next_op + 2, nextnext_op);
			skip_hds(next_op + 2, nextnext_op, r_pipes);
			return (exe_list(nextnext_op + 2, is_child, env, r_pipes));
		}
		skip_hds(next_op + 2, next_op + ft_strlen(next_op + 2), r_pipes);
		return (ret);
	}
	return (exe_pipeline(list, is_child, env, r_pipes));
}

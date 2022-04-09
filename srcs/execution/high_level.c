/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   high_level.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 11:41:43 by maabidal          #+#    #+#             */
/*   Updated: 2022/04/09 09:27:10 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	**skip_hds(char *beg_list, char *end_list, int **r_pipes)
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

static void	exe_pipes(t_p_data data, t_env *env, int **r_pipes);

static void	parent_pipe(t_p_data data, char *next_p, t_env *env, int **r_pipes)
{
	r_pipes = skip_hds(data.line, next_p, r_pipes);
	if (data.p_read != -1)
		ft_close(data.p_read);
	data.p_read = data.p_fds[READ];
	if (data.p_fds[WRITE] != -1)
		ft_close(data.p_fds[WRITE]);
	if (next_p)
	{
		data.line = next_p;
		exe_pipes(data, env, r_pipes);
		ms_waitpid(data.pid);
	}
	else
		env->exit_status = ms_waitpid(data.pid);
}

static void	exe_pipes(t_p_data data, t_env *env, int **r_pipes)
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
		ft_exit(exe_cmd_s(data.line, 1, *env, r_pipes));
	}
	parent_pipe(data, next_p, env, r_pipes);
}

static void	exe_pipeline(char *line, int is_child, t_env *env, int **r_pipes)
{
	t_p_data	data;

	data.line = line;
	data.is_child = is_child;
	data.p_read = -1;
	if (strchr_qp(line, '|'))
		exe_pipes(data, env, r_pipes);
	else
		env->exit_status = exe_cmd_s(line, is_child, *env, r_pipes);
}

void	exe_list(char *list, int is_child, t_env *env, int **r_pipes)
{
	char	*next_op;
	char	*nextnext_op;

	next_op = strstr_qp(list, "||");
	if (strstr_qp(list, "&&") && (!next_op || strstr_qp(list, "&&") < next_op))
		next_op = strstr_qp(list, "&&");
	if (next_op)
	{
		exe_pipeline(sub(list, next_op), is_child, env, r_pipes);
		if ((env->exit_status != 0) == (*next_op == '|'))
			return (exe_list(next_op + 2, is_child, env, r_pipes));
		nextnext_op = tern(*next_op == '|', "&&", "||");
		if (strstr_qp(next_op + 2, nextnext_op))
		{
			nextnext_op = strstr_qp(next_op + 2, nextnext_op);
			skip_hds(next_op + 2, nextnext_op, r_pipes);
			exe_list(nextnext_op + 2, is_child, env, r_pipes);
		}
		else
			skip_hds(next_op + 2, next_op + ft_strlen(next_op), r_pipes);
	}
	else
		exe_pipeline(list, is_child, env, r_pipes);
}

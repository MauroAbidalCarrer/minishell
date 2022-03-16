/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   high_level.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 11:41:43 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/16 17:12:45 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	child_pipe(t_p_data data, char *next_p, char **env)
{
	if (next_p)
		data.line = sub(data.line, next_p - 1);
	if (data.p_fds[READ] != -1)
		ft_close(data.p_fds[READ]);
	if (data.p_fds[WRITE] != -1)
		ft_dup2(data.p_fds[WRITE], WRITE);
	if (data.p_read != -1)
		ft_dup2(data.p_read, READ);
	ft_exit(exe_cmd_s(data.line, 1, env));
}

int	exe_pipes(t_p_data data, char **env);

int	parent_pipe(t_p_data data, char *next_p, char **env)
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
		ret = exe_pipes(data, env);
		ft_waitpid(data.pid);
		return (ret);
	}
	else
		return (ft_waitpid(data.pid));
}

int	exe_pipes(t_p_data data, char **env)
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
	if (data.pid == 0)
		child_pipe(data, next_p, env);
	return (parent_pipe(data, next_p, env));
}

int	exe_pipeline(char *line, int is_child, char **env)
{
	t_p_data	data;

	data.line = line;
	data.is_child = is_child;
	data.p_read = -1;
	if (strchr_qp(line, '|'))
		return (exe_pipes(data, env));
	return (exe_cmd_s(line, is_child, env));
}

int	exe_list(char *list, int is_child, char **env)
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
		ret = exe_pipeline(sub(list, next_and), 0, env);
		if (!ret)
			return (exe_list(sub(next_and + 2, end), 0, env));
		return (ret);
	}
	else if ((next_or && !next_and) || (next_or && next_and > next_or))
	{
		ret = exe_pipeline(sub(list, next_or), 0, env);
		if (ret)
			return (exe_list(sub(next_or + 2, end), 0, env));
		return (0);
	}
	return (exe_pipeline(list, is_child, env));
}

/*
char	*g_exe_name;
t_list	*g_ptrs_lst;

int	main(int ac, char **av, char **env)
{
	g_exe_name = av[0];
	int ret = exe_list(av[1], 0, env);
	printf("ret = %d\n",  ret);
	ft_exit(ret);
	ft_exit(0);
}
//MUST BE IN EXECUTION
//gcc -g3 *.c ../parsing_utils/ *.c 
//-I ../parsing_utils/ -I ../libft -L../libft/ -lft -lreadline 
//&& valgrind --track-fds=yes -s ./a.out 
//"ls | cat | cat | cat |cat && echo salut 
//<<q&& (false || mkdir new_dir)  || ls <set_cmd.c >oui >>non"
*/

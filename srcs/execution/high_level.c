/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   high_level.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 11:41:43 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/11 11:41:44 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	child_pipe(t_p_data data, char *next_p, char **env)
{
	if (next_p)
		data.line = sub(data.line, next_p - 1);
g_exe_name = data.line;
//printf("child about to exe [%s]\n", data.line);
	if (data.p_fds[READ] != -1)
{
		ft_close(data.p_fds[READ]);
//printf("[%s]close on p_fds[READ] done\n", data.line);
}
	if (data.p_fds[WRITE] != -1)
{
		ft_dup2(data.p_fds[WRITE], WRITE);
//printf("[%s]dup2 on write done\n", data.line);
}
	if (data.p_read != -1)
{
		ft_dup2(data.p_read, READ);
//printf("[%s]dup2 on p_read done\n", data.line);
}
	ft_exit(exe_cmd_s(data.line, 1, env));
}

int	exe_pipes(t_p_data data, char **env);

int	parent_pipe(t_p_data data, char *next_p, char **env)
{
	int	ret;

//READ, WRITE, p_read, p_fds
	if (data.p_read != -1)
		ft_close(data.p_read);
//READ, WRITE, p_fds
	data.p_read = data.p_fds[READ];
//READ, WRITE, p_read, p_fds[WRITE]
	if (data.p_fds[WRITE] != -1)
		ft_close(data.p_fds[WRITE]);
//READ, WRITE, p_read
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
//READ,  WRITE, p_read
	next_p = strchr_qp(data.line, '|');	
	if (next_p)
	{
		next_p++;
		ft_pipe(data.p_fds);//READ, WRITE, p_read, p_fds
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
	t_p_data data;

	data.line = line;
	data.p_read = -1;
	if (strchr_qp(line, '|'))
		return exe_pipes(data, env);
printf(";did not found pipe\n");
	return exe_cmd_s(line, is_child, env);
}

int	exe_list(char *list, int is_child, char **env)
{
	char	*next_and;
	char	*next_or;
	char	*end;
	int	ret;

	next_and = strstr_qp(list, "&&");
	next_or = strstr_qp(list, "||");
	end = list + ft_strlen(list);
	if (next_and < next_or)
	{
		ret = exe_pipeline(sub(list, next_and), is_child, env);
		if (!ret)
			return (exe_list(sub(next_and, end), is_child, env));
		return (ret); 
	}
	else if (next_or < next_and)
	{
		ret = exe_pipeline(sub(list, next_and), is_child, env);
		if (ret)
			return (exe_list(sub(next_and, end), is_child, env));
		return (0); 
	}
	return (exe_cmd_s(list, is_child, env));
} 

char	*g_exe_name;
t_list	*g_ptrs_lst;

int	main(int ac, char **av, char **env)
{
	g_exe_name = av[0];
	if (str_equal(av[1], "pipeline"))
	{
		printf("testing with [%s]\n", av [2]);
		int ret = exe_pipeline(av[2], 0, env);
		printf("ret = %d\n",  ret);
		ft_exit(ret);
	}
	ft_exit(0);
}

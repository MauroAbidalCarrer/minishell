/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 16:49:26 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/23 16:13:00 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	exe_extern_child(t_cmd cmd, char *cmd_s, t_env env)
{
	if (set_read(cmd_s, env) || set_write(cmd_s, env))
		ft_exit(1);
	if (cmd.ac == 0)
		ft_exit(0);
	cmd.path = get_path(cmd.av[0], *env.env);
	if (cmd.path == NULL)
		ft_exit(127);
	if (access(cmd.path, X_OK) == -1)
	{
		write_error(NULL, cmd.path, NULL);
		ft_exit(1);
	}
	execve(cmd.path, cmd.av, *env.env);
	write_error(NULL, cmd.av[0], NULL);
	ft_exit(1);
}

int	exe_extern_pp(t_cmd cmd, char *cmd_s, t_env env)
{
	pid_t	pid;

	pid = ft_fork();
	if (pid)
		return (ms_waitpid(pid));
	exe_extern_child(cmd, cmd_s, env);
	return (1);
}

int	exe_builtin_child(t_cmd cmd, char *cmd_s, t_env env)
{
	if (set_read(cmd_s, env) || set_write(cmd_s, env))
		return (1);
	if (cmd.ac == 0)
		return (0);
	return ((*cmd.builtin)(cmd.ac, cmd.av, env.env));
}

int	exe_builtin_pp(t_cmd cmd, char *cmd_s, t_env env)
{
	int	ret;
	int	saved_read;
	int	saved_write;

	saved_read = dup(READ);
	saved_write = dup(WRITE);
	ret = exe_builtin_child(cmd, cmd_s, env);
	ft_dup2(saved_read, READ);
	ft_dup2(saved_write, WRITE);
	return (ret);
}

int	exe_cmd_s(char *cmd_s, int is_child, t_env env)
{
	t_cmd		cmd;
	char		*n_p;

	n_p = strchr_q(cmd_s, '(');
	if (n_p)
	{
		cmd_s = sub(n_p + 1, to_ending_par(n_p));
		if (is_child)
			ft_exit(exe_list(cmd_s, is_child, env));
		else
			return (exe_list(cmd_s, is_child, env));
	}
	set_acav(&cmd, cmd_s);
	cmd.builtin = NULL;
	if (cmd.ac > 0)
		set_builtin(&cmd);
	if (cmd.builtin && is_child)
		ft_exit(exe_builtin_child(cmd, cmd_s, env));
	if (cmd.builtin && !is_child)
		return (exe_builtin_pp(cmd, cmd_s, env));
	if (!cmd.builtin && is_child)
		exe_extern_child(cmd, cmd_s, env);
	return (exe_extern_pp(cmd, cmd_s, env));
}

/*
char	*g_exe_name;
t_list	*g_ptrs_lst;
int	main(int ac, char **av, char **env)
{
	g_exe_name = av[0];
	if (str_equal(av[2], "parent"))
	{
		int	ret = exe_cmd_s(av[1], 0, env);
		printf("ret = %d\n", ret);
		ft_exit(ret);
	}
	else if (str_equal(av[2], "child"))
	{
		int	ret = exe_cmd_s(av[1], 1, env);
		printf("ret = %d\n", ret);
		ft_exit(ret);
	}
}
*/

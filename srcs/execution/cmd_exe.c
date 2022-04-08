/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 16:49:26 by maabidal          #+#    #+#             */
/*   Updated: 2022/04/08 14:54:38 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*expand_all(char *str, t_env env);

static void	exe_extern_child(t_cmd cmd, char *cmd_s, t_env env, int **r_pipes)
{
	int	ret;

	if (set_streams(cmd_s, r_pipes, 1))
		ft_exit(1);
	if (cmd.ac == 0)
		ft_exit(0);
	if (set_path(cmd.av[0], *env.env, &ret, &cmd.path))
		ft_exit(ret);
	execve(cmd.path, cmd.av, *env.env);
	write_error(NULL, cmd.av[0], NULL);
	ft_exit(1);
}

static int	exe_extern_pp(t_cmd cmd, char *cmd_s, t_env env, int **r_pipes)
{
	pid_t	pid;

	pid = ft_fork();
	if (!pid)
		exe_extern_child(cmd, cmd_s, env, r_pipes);
	return (ms_waitpid(pid));
}

static void	exe_builtin_child(t_cmd cmd, char *cmd_s, t_env env, int **r_pipes)
{
	if (set_streams(cmd_s, r_pipes, 1))
		ft_exit(1);
	if (cmd.ac == 0)
		ft_exit(0);
	ft_exit((*cmd.builtin)(cmd.ac, cmd.av, env));
}

static int	exe_builtin_pp(t_cmd cmd, char *cmd_s, t_env env, int **r_pipes)
{
	int	ret;
	int	saved_read;
	int	saved_write;

	saved_read = dup(READ);
	saved_write = dup(WRITE);
	ret = 0;
	if (set_streams(cmd_s, r_pipes, 0))
		ret = 1;
	else if (cmd.ac != 0)
		ret = (*cmd.builtin)(cmd.ac, cmd.av, env);
	ft_dup2(saved_read, READ);
	ft_dup2(saved_write, WRITE);
	return (ret);
}

//ac can be equal to 0 if there are only redirections
int	exe_cmd_s(char *cmd_s, int is_child, t_env env, int **r_pipes)
{
	t_cmd		cmd;
	char		*n_p;

	n_p = strchr_q(cmd_s, '(');
	if (n_p)
	{
		cmd_s = sub(n_p + 1, to_ending_par(n_p));
		if (is_child)
			ft_exit(exe_list(cmd_s, is_child, env, r_pipes));
		else
			return (exe_list(cmd_s, is_child, env, r_pipes));
	}
	cmd_s = expand_all(cmd_s, env);
	set_acav(&cmd, cmd_s);
	set_builtin(&cmd);
	if (cmd.builtin && is_child)
		exe_builtin_child(cmd, cmd_s, env, r_pipes);
	if (cmd.builtin && !is_child)
		return (exe_builtin_pp(cmd, cmd_s, env, r_pipes));
	if (!cmd.builtin && is_child)
		exe_extern_child(cmd, cmd_s, env, r_pipes);
	return (exe_extern_pp(cmd, cmd_s, env, r_pipes));
}

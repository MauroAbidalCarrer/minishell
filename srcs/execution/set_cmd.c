/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:08:08 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/17 17:04:00 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	set_read(char *cmd_s)
{
	int		p_fds[2];
	char	*last_hd;
	char	*last_if;

	last_if = NULL;
	last_hd = apply_heredocs(cmd_s, p_fds);
	if (apply_infile(cmd_s, &last_if))
	{
		if (last_hd)
		{
			ft_close(p_fds[READ]);
			ft_close(p_fds[WRITE]);
		}
		return (1);
	}
	if (last_hd && (!last_if || (last_hd > last_if)))
		ft_dup2(p_fds[READ], READ);
	if (last_hd)
		ft_close(p_fds[WRITE]);
	return (0);
}

int	set_write(char *cmd_s)
{
	int	flags;

	while (strchr_q(cmd_s, '>'))
	{
		cmd_s = strchr_q(cmd_s, '>') + 1;
		flags = CREAT_F;
		if (*cmd_s == '>')
			flags = APPEND_F;
		cmd_s += (*cmd_s == '>');
		if (fredi(sub_argument(cmd_s), flags, WRITE))
			return (1);
		cmd_s = skip_argument(cmd_s);
	}
	return (0);
}

//no parenthees are possible here
void	set_acav(t_cmd *cmd, char *cmd_s)
{
	char	*tmp;
	int		i;

	cmd->ac = 0;
	tmp = cmd_s;
	while (*tmp)
	{
		tmp = skip_spaces(tmp);
		if (starts_by_f_redi(tmp))
			tmp = starts_by_f_redi(tmp);
		else if (*tmp)
			cmd->ac++;
		tmp = skip_argument(tmp);
	}
	cmd->av = ft_calloc(cmd->ac + 1, sizeof(char *));
	i = 0;
	while (*cmd_s)
	{
		cmd_s = skip_spaces(cmd_s);
		if (starts_by_f_redi(cmd_s))
			cmd_s = starts_by_f_redi(cmd_s);
		else if (*cmd_s)
			cmd->av[i++] = sub_argument(cmd_s);
		cmd_s = skip_argument(cmd_s);
	}
}

void	set_builtin(t_cmd *cmd)
{
	if (str_equal(cmd->av[0], "echo"))
		cmd->builtin = &ms_echo;
	else if (str_equal(cmd->av[0], "cd"))
		cmd->builtin = &ms_cd;
	else if (str_equal(cmd->av[0], "pwd"))
		cmd->builtin = &ms_pwd;
	else if (str_equal(cmd->av[0], "export"))
		cmd->builtin = &ms_export;
	else if (str_equal(cmd->av[0], "unset"))
		cmd->builtin = &ms_unset;
	else if (str_equal(cmd->av[0], "env"))
		cmd->builtin = &ms_env;
	else if (str_equal(cmd->av[0], "exit"))
		cmd->builtin = &ms_exit;
	else
		cmd->builtin = NULL;
}

char	*get_path(char *name, char **env)
{
	char	*path;
	char	*paths;

	if (strchr(name, '/'))
		return (name);
	if (get_env_var("PATH", &paths, env))
	{
		ft_putstr_fd(ft_strjoin(name, CMD_NFOUND), 2);
		return (NULL);
	}
	name = ft_strjoin("/", name);
	while (paths)
	{
		path = ft_substr(paths, 0, ilen_strchr(paths, ':'));
		path = ft_strjoin(path, name);
		if (access(path, F_OK) == 0)
			return (path);
		paths = strchr(paths, ':');
		paths += (paths != NULL);
	}
	ft_putstr_fd(ft_strjoin(name + 1, CMD_NFOUND), 2);
	return (NULL);
}

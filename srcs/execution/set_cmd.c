/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:08:08 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/11 04:37:23 by maabidal         ###   ########.fr       */
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
	{
		ft_close(p_fds[READ]);
		ft_close(p_fds[WRITE]);
	}
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
		cmd->ac += (*tmp && !starts_by_f_redi(&tmp));
		tmp = skip_argument(tmp);
	}
	tmp = cmd_s;
	cmd->av = ft_malloc(sizeof(char *) * (cmd->ac + 1));
	cmd->av[cmd->ac] = NULL;
	i = 0;
	while (*tmp)
	{
		tmp = skip_spaces(tmp);
		if (*tmp && !starts_by_f_redi(&tmp))
			cmd->av[i++] = sub_argument(tmp);
		tmp = skip_argument(tmp);
	}
}

/*
int ms_echo(int ac, char **av, char **env){return (0);}
int ms_cd(int ac, char **av, char **env){return (0);}
int ms_exit(int ac, char **av, char **env){return (0);}
int ms_pwd(int ac, char **av, char **env){return (0);}
int ms_export(int ac, char **av, char **env){return (0);}
int ms_unset(int ac, char **av, char **env){return (0);}
int ms_env(int ac, char **av, char **env){return (0);}
*/

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
}

char	*get_path(char *name, char **env)
{
	char	*path;
	char	*paths;
	char	*err_msg;

	if (strchr(name, '/'))
		return (name);
	if (get_env_var("PATH", &paths, env))
		return (NULL);
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
	ft_putstr_fd(ft_strjoin(name + (*name == '/'), CMD_NFOUND), 2);
	return (NULL);
}

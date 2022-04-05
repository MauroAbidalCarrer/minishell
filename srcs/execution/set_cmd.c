/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:08:08 by maabidal          #+#    #+#             */
/*   Updated: 2022/04/05 16:05:15 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	set_read(char *cmd_s, int **r_pipes, int is_child)
{
	while (strchr_q(cmd_s, '<'))
	{
		cmd_s = strchr_q(cmd_s, '<') + 1;
		if (*cmd_s == '<')
		{
			ft_dup2(**r_pipes, READ);
			(*r_pipes)++;
			cmd_s++;
		}
		else if (fredi(sub_argument(cmd_s), READ_F, READ))
			return (1);
	}
	if (is_child)
	{
		while (**r_pipes != -1)
		{
			ft_close(**r_pipes);
			(*r_pipes)++;
		}
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

	if (ft_strchr(name, '/'))
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
		paths = ft_strchr(paths, ':');
		paths += (paths != NULL);
	}
	ft_putstr_fd(ft_strjoin(name + 1, CMD_NFOUND), 2);
	return (NULL);
}

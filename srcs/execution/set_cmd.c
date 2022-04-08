/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:08:08 by maabidal          #+#    #+#             */
/*   Updated: 2022/04/08 14:54:31 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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
	if (cmd->ac == 0)
	{
		cmd->builtin = NULL;
		return ;
	}
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

t_type	type_of(char *pathname)
{
	struct stat	f_stat;

	if (stat(pathname, &f_stat) == -1)
		return (write_error(NULL, pathname, NULL), error);
	if (S_ISREG(f_stat.st_mode))
		return (reg);
	if (S_ISDIR(f_stat.st_mode))
		return (dir);
	return (other);
}

static int	get_path(char *name, char **env, char **path)
{
	char	*paths;

	if (get_env_var("PATH", &paths, env))
	{
		ft_putstr_fd(ft_strjoin(name, CMD_NFOUND), 2);
		return (1);
	}
	name = ft_strjoin("/", name);
	while (paths)
	{
		*path = ft_substr(paths, 0, ilen_strchr(paths, ':'));
		*path = ft_strjoin(*path, name);
		if (access(*path, F_OK) == 0 && type_of(*path) == reg)
			return (0);
		paths = ft_strchr(paths, ':');
		paths += (paths != NULL);
	}
	ft_putstr_fd(ft_strjoin(name + 1, CMD_NFOUND), 2);
	return (1);
}

int	set_path(char *name, char **env, int *ret, char **path)
{
	if (strchr(name, '/'))
		*path = name;
	else if (get_path(name, env, path))
		return (*ret = 127, 1);
	if (type_of(*path) == error)
	{
		if (access(*path, F_OK) == -1)
			return (*ret = 127, 1);
		return (*ret = 126, 1);
	}
	if (type_of(*path) == dir)
	{
		write_error(NULL, *path, "Is a directory");
		return (*ret = 126, 1);
	}
	if (type_of(*path) == other)
	{
		write_error(NULL, *path, "Is not a regular file");
		return (*ret = 126, 1);
	}
	if (access(*path, X_OK) == -1)
		return (write_error(NULL, *path, NULL), *ret = 126, 1);
	return (0);
}

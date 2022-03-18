/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:38:51 by jmaia             #+#    #+#             */
/*   Updated: 2022/03/18 19:32:58 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "main.h"

static char	*get_path_in_cdpath(char *path, char **env);
static int	is_folder_accessible(char *path);
static int	ms_chdir(char const *prog_name, char const *path);
static char	*get_err_msg(char const *prog_name, char const *path);

static void	set_env_var(char *key, char *value)
{
printf("template set_env_var, ket = [%s], value = [%s]\n", key, value);
}

int	ms_cd(int ac, char **av, char ***env)
{
	char	*path;
	int		err;

	err = 0;
	if (ac == 1)
	{
		if (get_env_var("HOME", &path, *env))
		{
			err = (!err && ft_write(2, av[0], ft_strlen(av[0])) == -1);
			err = (!err && ft_write(2, ": cd: HOME not set\n", 19) == -1);
			return (1);
		}
	}
	else if (ac == 2)
		path = get_path_in_cdpath(av[1], *env);
	else
	{
		err = (!err && ft_write(2, av[0], ft_strlen(av[0])) == -1);
		err = (!err && ft_write(2, ": cd: too many arguments\n", 25) == -1);
		return (1);
	}
	return (ms_chdir(av[0], path));
}

static char	*get_path_in_cdpath(char *path, char **env)
{
	char	*sub_path;
	char	*paths;

	if (!ft_strcmp(path, "..") || !ft_strcmp(path, "."))
		return (path);
	if (strchr(path, '/'))
		return (path);
	if (get_env_var("CDPATH", &paths, env))
		return (path);
	sub_path = ft_strjoin("/", path);
	while (paths)
	{
		sub_path = ft_substr(paths, 0, ilen_strchr(paths, ':'));
		sub_path = ft_strjoin(sub_path, sub_path);
		if (is_folder_accessible(sub_path))
			return (sub_path);
		paths = strchr(paths, ':');
		paths += (paths != NULL);
	}
	ft_putstr_fd(ft_strjoin(path + (*path == '/'), CMD_NFOUND), 2);
	return (path);
}

static int	is_folder_accessible(char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (!dir)
		return (0);
	closedir(dir);
	return (1);
}

static int	ms_chdir(char const *prog_name, char const *path)
{
	int		err;
	char	*err_msg;
	char	*cwd;

	err = (chdir(path) == -1);
	if (err)
	{
		err_msg = get_err_msg(prog_name, path);
		perror(err_msg);
		ft_free(err_msg);
		return (err);
	}
	cwd = getcwd(0, 0);
	if (!cwd)
	{
		perror(prog_name);
		ft_exit(1);
	}
	set_env_var("PWD", cwd);
	free(cwd);
	return (0);
}

static char	*get_err_msg(char const *prog_name, char const *path)
{
	char	*err_msg;

	err_msg = ft_malloc(sizeof(*err_msg) * (ft_strlen(prog_name)
				+ ft_strlen(path) + 9));
	ft_memcpy(err_msg, prog_name, ft_strlen(prog_name));
	ft_memcpy(err_msg + ft_strlen(prog_name), ": cd: ", 6);
	ft_memcpy(err_msg + ft_strlen(prog_name) + 6, path, ft_strlen(path));
	ft_memcpy(err_msg + ft_strlen(prog_name) + 6 + ft_strlen(path), 0, 1);
	return (err_msg);
}

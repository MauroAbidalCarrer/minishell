/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:38:51 by jmaia             #+#    #+#             */
/*   Updated: 2022/04/05 15:08:00 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "main.h"

static char	*get_path_in_cdpath(char *path, char **env);
static int	is_folder_accessible(char *path);
static int	ms_chdir(char const *prog_name, char const *path, t_env env);
static char	*get_err_msg(char const *path);

int	ms_cd(int ac, char **av, t_env env)
{
	char	*path;
	int		err;

	if (ac == 1)
	{
		err = get_env_var("HOME", &path, *env.env);
		if (err)
		{
			write_error(NULL, "cd", "HOME not set");
			return (1);
		}
	}
	else if (ac == 2)
		path = get_path_in_cdpath(av[1], *env.env);
	else
	{
		write_error(NULL, "cd", "too many arguments");
		return (1);
	}
	if (ft_strcmp(path, ""))
		return (ms_chdir(av[0], path, env));
	return (0);
}

static char	*get_path_in_cdpath(char *path, char **env)
{
	char	*full_path;
	char	*paths;
	char	*sub_path;

	if (!ft_strcmp(path, "..") || !ft_strcmp(path, "."))
		return (path);
	if (ft_strchr(path, '/'))
		return (path);
	if (get_env_var("CDPATH", &paths, env))
		return (path);
	sub_path = ft_strjoin("/", path);
	while (paths)
	{
		full_path = ft_substr(paths, 0, ilen_strchr(paths, ':'));
		full_path = ft_strjoin(full_path, sub_path);
		if (is_folder_accessible(full_path))
			printf("%s\n", full_path);
		if (is_folder_accessible(full_path))
			return (full_path);
		paths = ft_strchr(paths, ':');
		paths += (paths != NULL);
	}
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

static int	ms_chdir(char const *prog_name, char const *path, t_env env)
{
	int		err;
	char	*err_msg;
	char	*cwd;
	char	*old_pwd;

	err = (chdir(path) == -1);
	if (err)
	{
		err_msg = get_err_msg(path);
		write_error(NULL, err_msg, NULL);
		ft_free(err_msg);
		return (err);
	}
	cwd = getcwd(0, 0);
	if (!cwd)
		perror(prog_name);
	if (!cwd)
		return (1);
	if (get_env_var("PWD", &old_pwd, *env.env) != 0)
		delete_env_var("OLDPWD", env.env);
	else
		set_env_var("OLDPWD", old_pwd, env.env);
	set_env_var("PWD", cwd, env.env);
	free(cwd);
	return (0);
}

static char	*get_err_msg(char const *path)
{
	char	*err_msg;

	err_msg = ft_malloc(sizeof(*err_msg) * (ft_strlen(path) + 7));
	ft_memcpy(err_msg, "cd: ", 4);
	ft_memcpy(err_msg + 4, path, ft_strlen(path));
	ft_memcpy(err_msg + 4 + ft_strlen(path), "", 1);
	return (err_msg);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:38:51 by jmaia             #+#    #+#             */
/*   Updated: 2022/02/23 18:21:07 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "main.h"

static char	*get_path_in_cdpath(char *path, char **env);
static int	get_index_of(const char *key, const char **tab);

int	ms_cd(int ac, char **av, char ***env)
{
	char	*path;
	int		err;

	err = 0;
	if (ac == 1)
	{
		if (get_env_var("HOME", &path, *env))
		{
			err = !err && (ft_write(2, av[0], ft_strlen(av[0])) == -1);
			err = !err && (ft_write(2, ": cd: HOME not set\n", 19) == -1);
			return (1);
		}
	}
	else if (ac == 2)
		path = get_path_in_cdpath(av[1], *env);
	else
	{
		err = !err && (ft_write(2, av[0], ft_strlen(av[0])) == -1);
		err = !err && (ft_write(2, ": cd: too many arguments\n", 25) == -1);
		return (1);
	}
	/* NEED TO BE DELETED */
	/* WIP : Change directory here in env and with function */
}

static char	*get_path_in_cdpath(char *path, char **env)
{
	char	*cdpath;
	char	*path_cdpath;

	if (!env)
		return (0);
	if (get_env_var("CDPATH", &cdpath, env))
		return (0);
	/* NEED TO BE DELETED */
	/* Hmm, si y'a moyen de chercher comme pour pipex avec le PATH, ça serait nickel, à voir, à completer*/
	(void) path;
	(void) path_cdpath;
	return (0);
}

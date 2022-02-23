/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:33:52 by maabidal          #+#    #+#             */
/*   Updated: 2022/02/12 23:20:50 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	has_access(char *cmd_path, t_cmd *cmd, int free_path_on_fail)
{
	if (access(cmd_path, F_OK) == 0)
	{
		if (access(cmd_path, X_OK) == 0)
			return (1);
		if (!free_path_on_fail)
			cmd->path = NULL;
		exit_with_error(cmd, NULL, *cmd->av, 126);
	}
	return (0);
}

//file names cannot contain '/'
//so it is safe to assume that if the cmd contains '/', it is an absolute path
//+ 1, car si '/' est a i=0 ca fait += 0
//when '' is called, zsh returns permission denied
//but if the the quotes qre full of spaces, it returns command not found idk why
int	is_special_case(t_cmd *cmd, char *cmd_s)
{
	if (!cmd->ac)
	{
		if (!*cmd_s)
			exit_with_error(cmd, PERM_DEN, *cmd->av, 127);
		else
			exit_with_error(cmd, CMD_NOT_FOUND, *cmd->av, 126);
	}
	if (index_of('/', *cmd->av, 0) != -1)
	{
		if (has_access(*cmd->av, cmd, 0))
		{
			cmd->path = *cmd->av;
			while (index_of('/', *cmd->av, 0) != -1)
				*cmd->av += index_of('/', *cmd->av, 0) + 1;
			return (1);
		}
		exit_with_error(cmd, CMD_NOT_FOUND, *cmd->av, 126);
	}
	return (0);
}

void	get_cmd_path(t_cmd *cmd, char **env)
{
	char	*path;
	char	*end_path;

	if (!try_get_env_var_vals("PATH", &path, env))
	{
		if (sub_cat("/", 1, *cmd->av, &end_path))
			exit_with_error(cmd, NULL, NULL, 1);
		while (*path)
		{
			if (sub_cat(path, index_of(':', path, 1), end_path, &cmd->path))
				exit_with_error(cmd, NULL, NULL, 1);
			if (has_access(cmd->path, cmd, 1))
			{
				free(end_path);
				return ;
			}
			free(cmd->path);
			cmd->path = NULL;
			path += index_of(':', path, 1);
			path += *path == ':';
		}
		free(end_path);
	}
	exit_with_error(cmd, CMD_NOT_FOUND, *cmd->av, 127);
}

void	setup_cmd_av(char *cmd_s, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd_s[i])
	{
		i += index_of(' ', cmd_s + i, 1);
		i += cmd_s[i] == ' ';
		cmd->ac++;
	}
	cmd->av = malloc(sizeof(char *) * (cmd->ac + 1));
	if (cmd->av == NULL)
		exit_with_error(NULL, NULL, NULL, 1);
	cmd->av[cmd->ac] = 0;
	cmd->ac = 0;
	while (*cmd_s)
	{
		while (*cmd_s == ' ')
			cmd_s++;
		if (sub_cat(cmd_s, index_of(' ', cmd_s, 1), 0, cmd->av + cmd->ac))
			exit_with_error(cmd, NULL, NULL, 1);
		cmd_s += index_of(' ', cmd_s, 1);
		cmd_s += *cmd_s == ' ';
		cmd->ac += cmd->av[cmd->ac] != NULL;
	}
}

void	setup_cmd(t_cmd *cmd, char *cmd_s, char **env)
{
	unsigned int	i;

	i = 0;
	while (i < sizeof(t_cmd))
		((unsigned char *)cmd)[i++] = 0;
	setup_cmd_av(cmd_s, cmd);
	if (!is_special_case(cmd, cmd_s))
		get_cmd_path(cmd, env);
}

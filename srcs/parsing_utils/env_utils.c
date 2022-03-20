/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 10:57:08 by jmaia             #+#    #+#             */
/*   Updated: 2022/03/18 11:43:58 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_utils.h"

static int	modify_env_var(char *key, char *value, char **env);
static void	replace_env_var(char **pos, char *key, char *value);

int	get_env_var(char *key, char **dst, char **env)
{
	int	i;
	int	j;

	if (!env)
		return (1);
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && key[j] && env[i][j] == key[j])
		{
			if (key[j + 1] == 0)
			{
				*dst = env[i] + j + 2;
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	set_env_var(char *key, char *value, char ***env)
{
	char	*env_var;
	char	*junk;
	char	**new_env;
	int		key_exist;
	size_t	value_len;

	key_exist = !get_env_var(key, &junk, *env);
	if (key_exist)
		return (!!value && modify_env_var(key, value, *env));
	new_env = ft_malloc(sizeof(*new_env) * (ft_arraylen((void **)*env) + 2));
	ft_memcpy(new_env, *env, sizeof(*new_env) * ft_arraylen((void **)*env));
	if (value)
		value_len = ft_strlen(value);
	else
		value_len = 0;
	env_var = ft_malloc(sizeof(*env_var) * (ft_strlen(key) + value_len + 2));
	ft_memcpy(env_var, key, ft_strlen(key));
	env_var[ft_strlen(key)] = '=';
	ft_memcpy(env_var + ft_strlen(key) + 1, value, value_len);
	env_var[ft_strlen(key) + value_len + 1] = 0;
	new_env[ft_arraylen((void **)*env)] = env_var;
	new_env[ft_arraylen((void **)*env) + 1] = 0;
	ft_free(env);
	*env = new_env;
	return (0);
}

static int	modify_env_var(char *key, char *value, char **env)
{
	int		i;
	char	*equal_pos;

	i = 0;
	while (env[i])
	{
		equal_pos = ft_strchr(env[i], '=');
		if (!equal_pos)
			equal_pos = env[i] + ft_strlen(equal_pos);
		*equal_pos = 0;
		if (!ft_strcmp(env[i], key))
		{
			*equal_pos = '=';
			replace_env_var(&env[i], key, value);
			return (0);
		}
		*equal_pos = '=';
		i++;
	}
	return (1);
}

static void	replace_env_var(char **pos, char *key, char *value)
{
	char	*new_var;

	new_var = ft_malloc(sizeof(*new_var) * (ft_strlen(key)
				+ ft_strlen(value) + 2));
	ft_memcpy(new_var, key, ft_strlen(key));
	ft_memcpy(new_var + ft_strlen(key), "=", 1);
	ft_memcpy(new_var + ft_strlen(key) + 1, value, ft_strlen(value));
	new_var[ft_strlen(key) + ft_strlen(value) + 1] = 0;
	ft_free(*pos);
	*pos = new_var;
}

int	delete_env_var(char *key, char ***env)
{
	char	**new_env;
	char	*key_ptr;
	int		i;
	int		j;

	i = get_env_var(key, &key_ptr, *env);
	if (i)
		return (0);
	new_env = ft_malloc(sizeof(*new_env) * ft_arraylen((void **)*env));
	i = 0;
	j = 0;
	while ((*env)[j])
	{
		if (ft_strchr((*env)[j], '=') + 1 != key_ptr)
			new_env[i++] = (*env)[j];
		j++;
	}
	new_env[i] = 0;
	ft_free(*env);
	*env = new_env;
	return (0);
}

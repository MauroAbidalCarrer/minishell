/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 12:17:32 by jmaia             #+#    #+#             */
/*   Updated: 2022/04/05 08:47:41 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char		*get_msg_err(char *arg);

static void	print_env(t_env env);
static void	sort_array(char **array, size_t size,
				int (*cmp)(char const *a, char const *b));
static int	has_valid_name(char const *var);
static int	export_var(char *var, t_env env);

int	ms_export(int ac, char **av, t_env env)
{
	char	*err_msg;
	int		i;
	int		err;

	if (ac == 1)
	{
		print_env(env);
		return (0);
	}
	i = 1;
	err = 0;
	while (av[i])
	{
		if (!has_valid_name(av[i]))
		{
			err = 1;
			err_msg = get_msg_err(av[i]);
			write_error(NULL, "export", err_msg);
			ft_free(err_msg);
		}
		else
			export_var(av[i], env);
		i++;
	}
	return (err);
}

static void	print_env(t_env env)
{
	size_t	env_size;
	size_t	i;
	char	**sorted_env;
	char	*escaped_var;
	char	*quoted_var;

	if (!*env.env)
		return ;
	env_size = 0;
	while ((*env.env)[env_size])
		env_size++;
	sorted_env = ft_malloc(sizeof(*sorted_env) * (env_size + 1));
	ft_memcpy(sorted_env, *env.env, sizeof(**env.env) * (env_size + 1));
	sort_array(sorted_env, env_size, &ft_strcmp);
	i = 0;
	while (i < env_size)
	{
		escaped_var = escape_quote_and_backslash(sorted_env[i]);
		quoted_var = quote_value(escaped_var);
		printf("declare -x %s\n", quoted_var);
		ft_free(quoted_var);
		i++;
	}
	ft_free(sorted_env);
}

static void	sort_array(char **array, size_t size,
				int (*cmp)(char const *a, char const *b))
{
	size_t	i;
	size_t	j;
	char	*tmp;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (cmp(array[i], array[j]) > 0)
			{
				tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static int	has_valid_name(char const *var)
{
	int	i;

	if (var[0] == '=' || var[0] == 0)
		return (0);
	if (var[0] >= '0' && var[0] <= '9')
		return (0);
	i = 0;
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	export_var(char *var, t_env env)
{
	char	*key;
	char	*value;
	size_t	size_key;
	size_t	size_value;

	if (!ft_strchr(var, '='))
	{
		set_env_var(var, 0, env.env);
		return (0);
	}
	size_key = (int)(ft_strchr(var, '=') - var) + 1;
	size_value = ft_strlen(var) - size_key + 1;
	key = ft_malloc(sizeof(*key) * size_key);
	value = ft_malloc(sizeof(*value) * size_value);
	ft_memcpy(key, var, size_key - 1);
	key[size_key - 1] = 0;
	ft_memcpy(value, var + size_key, size_value - 1);
	value[size_value - 1] = 0;
	set_env_var(key, value, env.env);
	ft_free(key);
	ft_free(value);
	(void) env;
	return (0);
}

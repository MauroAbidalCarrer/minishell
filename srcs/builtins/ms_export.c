/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 12:17:32 by jmaia             #+#    #+#             */
/*   Updated: 2022/03/04 15:53:20 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	print_env(char ***env);
static void	sort_array(char **array, size_t size,
				int (*cmp)(char const *a, char const *b));
static void	print_array(char **array, size_t size);
static int	export_var(char *var, char ***env);

int	ms_export(int ac, char **av, char ***env)
{
	int	i;

	(void) env;
	if (ac == 1)
	{
		print_env(env);
		return (0);
	}
	i = 1;
	while (av[i])
	{
		export_var(av[i], env);
		i++;
	}
	return (0);
}

static void	print_env(char ***env)
{
	size_t	env_size;
	char	**sorted_env;

	if (!env || !*env)
		return ;
	env_size = 0;
	while ((*env)[env_size])
		env_size++;
	sorted_env = ft_malloc(sizeof(*sorted_env) * (env_size + 1));
	ft_memcpy(sorted_env, *env, sizeof(**env) * (env_size + 1));
	sort_array(sorted_env, env_size, &ft_strcmp);
	print_array(sorted_env, env_size);
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

static void	print_array(char **array, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		printf("declare -x %s\n", array[i]);
		i++;
	}
}

static int	export_var(char *var, char ***env)
{
	char	*key;
	char	*value;
	size_t	size_key;
	size_t	size_value;

	size_key = (int)(ft_strchr(var, '=') - var) + 1;
	size_value = ft_strlen(var) - (int)(var - ft_strchr(var, '='));
	key = ft_malloc(sizeof(*key) * size_key);
	value = ft_malloc(sizeof(*value) * size_value);
	ft_memcpy(key, var, size_key - 1);
	key[size_key - 1] = 0;
	ft_memcpy(value, var + size_key, size_value - 1);
	value[size_value - 1] = 0;
	set_env_var(key, value);
	(void) env;
	return (0);
}

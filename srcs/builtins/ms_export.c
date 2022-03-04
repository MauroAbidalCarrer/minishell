/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 12:17:32 by jmaia             #+#    #+#             */
/*   Updated: 2022/03/04 12:59:44 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void		print_env(char ***env);
static size_t	get_array_size(char **env);
static void		sort_array(char **array,
					int (*cmp)(char const *a, char const *b));
static void		print_array(char **array, size_t size);

int	ms_export(int ac, char **av, char ***env)
{
	(void) av;
	(void) env;
	if (ac == 1)
	{
		print_env(env);
		return (0);
	}
	return (0);
}

static void	print_env(char ***env)
{
	size_t	env_size;
	char	**sorted_env;

	if (!env || !*env)
		return ;
	env_size = get_array_size(*env);
	sorted_env = ft_malloc(sizeof(*sorted_env) * (env_size + 1));
	ft_memcpy(sorted_env, *env, sizeof(**env) * (env_size + 1));
	sort_array(sorted_env, &ft_strcmp);
	print_array(sorted_env, env_size);
	ft_free(sorted_env);
}

static size_t	get_array_size(char **env)
{
	size_t	size;

	size = 0;
	while (env[size])
		size++;
	return (size);
}

static void	sort_array(char **array, int (*cmp)(char const *a, char const *b))
{
	size_t	i;
	size_t	j;
	char	*tmp;

	i = 0;
	while (i < get_array_size(array))
	{
		j = i + 1;
		while (j < get_array_size(array))
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

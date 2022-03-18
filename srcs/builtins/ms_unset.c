/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 11:37:00 by jmaia             #+#    #+#             */
/*   Updated: 2022/03/18 19:34:44 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	delete_env_var(char *key)
{
		printf("template delete_env_var, key=[%s]\n", key);
}


int	ms_unset(int ac, char **av, char ***env)
{
	int	i;

	(void) env;
	i = 1;
	while (i < ac)
	{
		delete_env_var(av[i]);
		i++;
	}
	return (0);
}

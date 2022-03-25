/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 11:37:00 by jmaia             #+#    #+#             */
/*   Updated: 2022/03/25 16:17:10 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ms_unset(int ac, char **av, t_env env)
{
	int	i;

	(void) env;
	i = 1;
	while (i < ac)
	{
		delete_env_var(av[i], env.env);
		i++;
	}
	return (0);
}

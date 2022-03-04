/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 13:58:52 by jmaia             #+#    #+#             */
/*   Updated: 2022/03/04 12:42:51 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ms_env(int ac, char **av, char ***env)
{
	int		i;
	int		err;

	(void) ac;
	(void) av;
	if (!env || !*env)
		return (0);
	i = 0;
	err = 0;
	while ((*env)[i] && !err)
	{
		err = (printf("%s\n", (*env)[i]) < 0);
		i++;
	}
	return (!!err);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 13:58:52 by jmaia             #+#    #+#             */
/*   Updated: 2022/03/04 16:57:25 by jmaia            ###   ########.fr       */
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
		if (ft_strchr((*env)[i], '='))
			err = (printf("%s\n", (*env)[i]) < 0);
		i++;
	}
	return (!!err);
}

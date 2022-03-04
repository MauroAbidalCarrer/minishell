/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:06:42 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/04 11:34:24 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	get_env_var(char const *key, char **dst, char **env)
{
	int	i;
	int	j;

	if (env == NULL)
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

/* NEED TO DELETED */
/* This function needs to be written */
int	set_env_var(char const *key, char const *value)
{
	(void) key;
	(void) value;
	return (0);
}

/* NEED TO DELETED */
/* This function needs to be written */
int delete_env_var(char const *key)
{
	(void) key;
	return (0);
}

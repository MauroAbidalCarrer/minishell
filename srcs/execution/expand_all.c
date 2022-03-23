/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:01:57 by jmaia             #+#    #+#             */
/*   Updated: 2022/03/23 15:23:19 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "var_expand.h"
#include "wildcard.h"

int	expand_all(char	*str, t_env env)
{
	char	*expanded_str;

	expanded_str = var_expand(str, *env.env, env.exit_status);
	expanded_str = wild_it(expanded_str);
	printf("Expanded_str : %s\n", expanded_str);
	return (0);
}

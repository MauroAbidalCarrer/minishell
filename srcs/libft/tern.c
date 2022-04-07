/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tern.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:23:19 by maabidal          #+#    #+#             */
/*   Updated: 2022/04/07 17:23:32 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*tern(int cond, char *a, char *b)
{
	if (cond)
		return (a);
	return (b);
}

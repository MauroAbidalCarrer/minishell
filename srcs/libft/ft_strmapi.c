/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 14:59:04 by maabidal          #+#    #+#             */
/*   Updated: 2022/02/22 15:24:45 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new;
	char	c;
	int		i;

	if (s == NULL)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	new = ft_malloc((i + 1) * sizeof(char));
	new[i] = 0;
	i = 0;
	while (s[i])
	{
		c = s[i];
		new[i] = (*f)((unsigned int)i, c);
		i++;
	}
	return (new);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:22:33 by maabidal          #+#    #+#             */
/*   Updated: 2022/02/22 19:12:11 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	starts_by_str(char *str, char *str2)
{
	while (*str && *str == *str2)
	{
		if (str2[1] = 0)
			rturn (1);
		str++;
		str2++;
	}
	return (0);
}

char	*skip(char *str, char c)
{
	while (*str == c && *str)
		str++;
	return (str);
}

char	*skip_to_n_ignore(char *str, char target, char *ignore)
{
	while (*str == c && *str)
	{
		
		str++;
	}
	return (str);
}

//check que les "/'/( sont fermees
int	is_closed(char *str, char op, char cl)
{
//1 = check que les ' et " sont closed
}

//check que les redirections/control operators sont entoures
int	str_is_valid_list(char *str)
{
	str = skip(str , ' ');
	
}

/*
tests:

cmd1 '"va"&&||'& cmd2||cmd2 etre|(cmd3>>file1)
	
*/

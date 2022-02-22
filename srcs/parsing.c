/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:22:33 by maabidal          #+#    #+#             */
/*   Updated: 2022/02/22 21:15:04 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int	starts_by_str(char *str, char *str2)
{
	while (*str && *str == *str2)
	{
		if (str2[1] = 0)
			return (1);
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

//bizarre comme fonction, mais ca passe... je crois
int	check_parentheses(char *str)
{
	char	*next;
	int	count;
	
	count = 0;
	while (*str)
	{
		if (*str == '(')
			count++;
		if(*str == ')')
			count--;
		if (count < 0)
			return (0);
		if (strchr("'\"", *str))
		{
			next = strchr(str + 1, *str);
			if (next == NULL)
				return (0);
			str = next;
		}
		str++;
	}
	return (count == 0);
}

int	check_quotes(char *str, char q, char other_q)
{
	char	*next;
	int	count;
	
	count = 0;
	while (*str)
	{
		count = (count + (*str == q)) % 2;
		if (*str == other_q)
		{
			next = strchr(str + 1, other_q);
			if (next == NULL)
				return (0);
			str = next;
		}
		str++;
	}
	return (count == 0);
}

//check que les redirections/control operators sont entoures
int	str_is_valid_list(char *str)
{
	if (!check_parentheses(str))
		return (0);
	if (!check_quotes(str, ''', '\"')
		return (0);
	if (!check_quotes(str, '\"', ''')
		return (0);
	return (1);
}

char	*g_exe_name;
t_list	*g_ptrs_lst;
int	main(int ac, char **av)
{
	printf("%d\n", str_is_valid_list(av[1]);
}

/*
tests:

cmd1 '"va"&&||'& cmd2||cmd2 etre|(cmd3>>file1)
	
*/

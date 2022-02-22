/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:22:33 by maabidal          #+#    #+#             */
/*   Updated: 2022/02/22 22:21:13 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int	is_str(char *str, char *str2)
{
	while (*str && *str2 && *str == *str2)
	{
		if (str2[1] == 0)
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

int	is_operator(char *str)
{
	if (is_str(str, "||") || is_str(str, "&&"))
		return (1);
	if (is_str(str, ">") || is_str(str, "<"))
		return (1);
	if (is_str(str, ">>") || is_str(str, "<<"))
		return (1);
	if (is_str(str, "|"))
		return (1);
	return (0);
}

char	*skip_quotes(char *str)
{
	if (*str == '\'' || *str == '\"')
		str = strchr(str + 1, *str);
	return (str);
}

int	check_operators(char *str)
{
	int	op_count;

printf("checking operators on [%s]\n", str);
	op_count = 0;
	while (*str)
	{
printf("%c\n", *str);
		op_count += is_operator(str);
printf("op_count = %d\n", op_count);
		if (op_count > 1)
			return (0);
		if (!is_operator(str) && !strchr(" \'\"", *str))
			op_count = 0;
printf("skipping quotes\n");
		str = skip_quotes(str);
		if (str == NULL)
			return (0);
		str++;
	}
	return (op_count == 0);
}

//bizarre comme fonction, mais ca passe... je crois
int	check_parentheses(char *str)
{
	char	*next;
	int	count;
	
	count = 0;
	while (*str)
	{
		count += (*str == '(');
		count -= (*str == ')');
		if (count < 0)
			return (0);
		str = skip_quotes(str);
		if (str == NULL)
			return (0);
		str++;
	}
	return (count == 0);
}

int	check_quotes(char *str)
{
	while (*str)
	{
		str = skip_quotes(str);
		if (str == NULL)
			return (0);
		str++;
	}
	return (1);
}

//check que les redirections/control operators sont entoures
int	str_is_valid_list(char *str)
{
	if (!check_parentheses(str))
		return (0);
	if (!check_quotes(str))
		return (0);
	if (!check_operators(str))
		return (0);
	return (1);
}

char	*g_exe_name;
t_list	*g_ptrs_lst;
int	main(int ac, char **av)
{

	char *valid_tests[50] =
	{
		"sa\"\"lut",
		"\'\"\'salut",
		"((((()))salut))",
		"((((()\")\"))salut))",
		"sa\"\'\"lut",
		"cmd1 \'\"va\"&&||\'& cmd2||cmd2 etre|(cmd3>>file1)",
		NULL
	};
	printf("testing valid inputs\n");
	for (int i = 0; valid_tests[i]; i++)
		printf("testing [%s]\n%d\n\n", valid_tests[i], str_is_valid_list(valid_tests[i]));
}

/*
tests:

cmd1 '"va"&&||'& cmd2||cmd2 etre|(cmd3>>file1)
	
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:22:33 by maabidal          #+#    #+#             */
/*   Updated: 2022/02/23 14:30:07 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

//#include "libft.h"
int	is_operator(char **str)
{
	int		i;
	char	*tests[7];
	char	*tmp;

	tests[0] = "||";
	tests[1] = "&&";
	tests[2] = "|";
	tests[3] = "<<";
	tests[4] = "<";
	tests[5] = ">";
	tests[6] = ">>";
	i = -1;
	while (++i < 7)
	{
		tmp = str_starts_by(*str, tests[i]);
		if (tmp != *str)
			return (1);
	}
	return (0);
}

int	check_operators(char *str)
{
	int	op_count;

	op_count = 1;
	while (*str)
	{
		if (is_operator(&str) && op_count++ == 1)
			return (0);
		if (!strchr(" \'\"|><\t\11\12\13", *str))
			op_count = 0;
		if (*str == '\'' || *str == '\"')
			str = strchr(str + 1, *str);
		if (str == NULL)
			return (0);
		str++;
	}
	return (op_count == 0);
}

//bizarre comme fonction, mais ca passe... je crois
int	check_parentheses(char *str)
{
	int		count;

	count = 0;
	while (*str)
	{
		count += (*str == '(');
		count -= (*str == ')');
		if (count < 0)
			return (0);
		if (*str == '\'' || *str == '\"')
			str = strchr(str + 1, *str);
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
		if (*str == '\'' || *str == '\"')
			str = strchr(str + 1, *str);
		if (str == NULL)
			return (0);
		str++;
	}
	return (1);
}

int	should_exe_list(char *str)
{
	if (!check_parentheses(str))
		return (0);
	if (!check_quotes(str))
		return (0);
	if (!check_operators(str))
		return (0);
	return (1);
}
/*
//& can be considred as a cmd
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
"cmd1 \'\"va\"&&||\'&&&&&&&&& cmd2||cmd2 etre|(cmd3>>file1)",
	"cmd1 \'\"va\"&&||\'& cmd2||cmd2 etre|(cmd3>>file1) &",
	NULL
};
char *invalid_tests[50] =
{
	"sa\"lut",
	"\'\'s\"alut",
	"((((())salut))",
	"(((((\")\"))salut))",
	"sa\"\'lut",
	"| cmd1 \'\"va\"&&||\'& cmd2||cmd2 etre|(cmd3>>file1) ",
	"cmd1 \'\"va\"&&||\'&&&&&&&&& cmd2|||||||||cmd2 etre|(cmd3>>file1)",
	"cmd1 \'\"va\"&&||\'& cmd2||cmd2 etre|(cmd3>>file1) &&",
	"cmd1 \'\"va\"&&||\'& cmd2||cmd2 etre|(cmd3>>file1) && ",
	"<cmd1 \'\"va\"&&||\'& cmd2||cmd2 etre|(cmd3>>file1)",
	"",
	"  ",
	" \t",
	NULL
};
printf("testing valid inputs\n");
for (int i = 0; valid_tests[i]; i++)
printf("testing [%s]\n%d\n\n", valid_tests[i], 
should_exe_list(valid_tests[i]));
printf("-----------\ntesting invalid inputs\n");
for (int i = 0; invalid_tests[i]; i++)
printf("testing [%s]\n%d\n\n", invalid_tests[i], 
should_exe_list(invalid_tests[i]));
}
*/

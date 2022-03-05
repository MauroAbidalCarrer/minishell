/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:22:33 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/06 00:42:36 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
//0 = no redi found
//1 = redi found and arg valid
//2 = redi found but arg not valid
int	check_file_redirection(char **str)
{
	if (starts_by_f_redi(str))
	{
		*str = strnochr(*str, ' ');
		if (**str && !starts_by_f_redi(str) && !starts_by_sep(str))
			if (**str != '(' && **str != ')')
				return (1);
		return (2);
	}
	return (0);
}

//warning: ugly function
char	*skip_argument(char *str)
{
	char	*tmp;

	while (*str && *str != ' ')
	{
		tmp = str;
		if (starts_by_sep(&tmp) || starts_by_f_redi(&tmp))
			break ;
		if (*str == '(' && *str == ')')
			break ;
		if (*str == '\'' || *str == '\"')
			str = strchr(str + 1, *str);
		str++;
	}
	return (str);
}

//check that file redirections are terminated
//check that there is at least one argument 
char	*check_cmd_s(char *str)
{
	int		nb_arg;
	int		redi_res;
	char	*tmp;

	nb_arg = 0;
	tmp = str;
	while (*str && !starts_by_sep(&tmp) && *str != '(' && *str != ')')
	{
		redi_res = check_file_redirection(&str);
		if (redi_res == 2)
			return (NULL);
		nb_arg += (redi_res == 0 && *str != ' ' && *str);
		str = skip_argument(str);
		str = skip_spaces(str);
		tmp = str;
	}
	if (nb_arg != 0)
		return (str);
	return (0);
}

//skip spaces
//check that there is no emmiter
//check for "emmitter"
//check for separator
//remember to check for stuff like this: cmd1 (| cmd2)
int	check_list(char *str)
{
	int	to_par;
	int	should_emmit;

	should_emmit = 1;
	while (*str)
	{
		str = skip_spaces(str);
		if (starts_by_sep(&str))
			return (0);
		if (*str == '(')
		{
			to_par = to_ending_par(str);
			if (to_par == 1 || !check_list(ft_substr(str, 1, to_par - 1)))
				return (0);
			str += to_par + 1;
		}
		else if (check_cmd_s(str))
			str = check_cmd_s(str);
		else
			return (0);
		str = skip_spaces(str);
		should_emmit = starts_by_sep(&str);
	}
	return (!should_emmit);
}

//check quotes must be first for skip_quotes
int	should_exe_list(char *str)
{
	if (!check_quotes(str))
		return (0);
	if (!check_parentheses(str))
		return (0);
	if (!check_list(str))
		return (0);
	return (1);
}
/*
char	*g_exe_name;
t_list	*g_ptrs_lst;
int	main(int ac, char **av)
{
	char *valid_tests[50] =
	{
		"sa\"\"lut",
		"\'\"\'salut",
"sa\"\'\"lut",
"cmd1 \'\"va\"&&||\'& cmd2||cmd2 etre|(cmd3>>file1)",
	"cmd1 \'\"va\"&&||\'& cmd2||cmd2 etre|(cmd3>>file1) &",
	"cmd1 \'\"va\"&&||\'& cmd2||cmd2 etre|(< cmd3 file1) ",
	"cmd1 \'\"va\"&&||\'& cmd2||cmd2 etre|(< cmd3 file1) ",
	"<cmd1 \'\"va\"&&||\'& cmd2||cmd2 etre|(cmd3>>file1)",
	NULL
};
char *invalid_tests[50] =
{
	")(",
	"sa\"lut",
	"\'\'s\"alut",
	"((((())salut))",
	"(((((\")\"))salut))",
	"sa\"\'lut",
"cmd1 \'\"va\"&&||\'&&&&&&&&& cmd2||cmd2 etre|(cmd3>>file1)",
	"| cmd1 \'\"va\"&&||\'& cmd2||cmd2 etre|(cmd3>>file1) ",
	"cmd1 \'\"va\"&&||\'&&&&&&&&& cmd2|||||||||cmd2 etre|(cmd3>>file1)",
	"cmd1 \'\"va\"&&||\'& cmd2||cmd2 etre|(cmd3>>file1) &&",
	"cmd1 \'\"va\"&&||\'& cmd2||cmd2 etre|(cmd3>>file1) && ",
	"cmd1 (|cmd2)",
	"()",
	"cmd1 (| cmd2)",
	"<",
	"",
	"  ",
	" \t",
	NULL
};
printf("testing valid inputs\n");
for (int i = 0; valid_tests[i]; i++)
{
printf("testing [%s]\n", valid_tests[i]); 
printf("%d\n\n", should_exe_list(valid_tests[i]));
}
printf("-----------\ntesting invalid inputs\n");
for (int i = 0; invalid_tests[i]; i++)
printf("testing [%s]\n%d\n\n", invalid_tests[i], 
should_exe_list(invalid_tests[i]));
}
*/

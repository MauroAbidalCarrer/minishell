/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:22:33 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/08 16:44:52 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	check_file_redirection(char **str)
{
	if (starts_by_f_redi(str))
	{
		*str = strnochr(*str, ' ');
		if (**str && !starts_by_f_redi(str) && !starts_by_sep(str))
			if (**str != '(' && **str != ')')
				return (1);
		return (0);
	}
	return (1);
}

//check that file redirections are terminated
//check that there is at least one argument or one valid f_redi
char	*check_cmd_s(char *str)
{
	int		nb_arg;
	char	*tmp;

	nb_arg = 0;
	tmp = str;
	while (*str && !starts_by_sep(&tmp) && *str != '(' && *str != ')')
	{
		if (!check_file_redirection(&str))
			return (NULL);
		nb_arg += (skip_argument(str) != str);
		str = skip_argument(str);
		str = skip_spaces(str);
		tmp = str;
	}
	if (nb_arg != 0)
		return (str);
	return (0);
}

int	there_is_unexpected_token(char *str)
{
	char	*tmp;

	tmp = str;
	if (starts_by_sep(&str))
	{
		ft_putstr_fd(g_exe_name, 2);
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putchar_fd(*tmp, 2);
		if (tmp[1] == '|' || tmp[1] == '&')
			ft_putchar_fd(tmp[1], 2);
		ft_putstr_fd("\'\n", 2);
		return (1);
	}
	return (0);
}

//skip spaces
//check that there is no emmiter
//check for "emmitter"
//check for separator
//remember to check for stuff like this: cmd1 (| cmd2)
int	should_exe_list(char *str)
{
	int	i;

	if (!check_quotes(str) || !check_parentheses(str))
		return (0);
	i = 1;
	while (*str)
	{
		str = skip_spaces(str);
		if (there_is_unexpected_token(str))
			return (0);
		if (*str == '(')
		{
			i = to_ending_par(str);
			if (!should_exe_list(ft_substr(str, 1, i - 1)))
				return (0);
			str += i + 1;
		}
		else if (check_cmd_s(str))
			str = check_cmd_s(str);
		else
			return (0);
		str = skip_spaces(str);
		i = starts_by_sep(&str);
	}
	return (!i);
}

/*
char	*g_exe_name;
t_list	*g_ptrs_lst;
int	main(int ac, char **av)
{
	g_exe_name = av[0];
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
	"<cmd1",
	"<file1 | cmd1",
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
	"cmd1 \'\"va\' cmd2|||||||||cmd2 etre|(cmd3>>file1)",
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
ft_exit(0);
}
//gcc checker.c utils.c ../parsing_utils/ *.c -I 
//../parsing_utils -I ../libft/ -L ../libft -l ft && ./a.out
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:22:33 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/14 20:14:35 by maabidal         ###   ########.fr       */
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
//parentheses are considered as cmds
//if (parentheses)
//	no redirections are allowed before the prentheses
//	if an heredocs is present before a parenthese,
//	it should be executed and update the history
//	redirections are allowed after the parentheses
//	no arguments are allowed
//else
//	check that there is at least one argument or one valid f_redi
char	*skip_cmd_s(char *str, int expected)
{
	str = sub_cmd_s(str);
	if (strchr_q(str, '('))
	{

	}
	
}

char	*skip_sep(char *str, int expected)
{
	char	*err_msg;
	char	*tmp;

	str = skip_spaces(str);
	tmp = str;
	if (starts_by_sep(&str))
	{
		if (!expected)
		{
			err_msg = g_exe_name;
			err_msg = ft_strjoin(err_msg, ERR_PRE);
			err_msg = straddchar(err_msg, *tmp);
			err_msg = ft_strjoin(err_msg, "\"\n");
			ft_putstr_fd(err_msg, 2);
		}
		return (str);
	}
	return (NULL);
}

int	should_exe_list(char *str)
{
	char 	(*skip_expected_token)(char *);
	char 	(*skip_unexpected_token)(char *);
	char	*tmp;

	if (!quotes_closed(str) || !parentheses_closed(str))
		return (0);
	skip_expected_token = &check_cmd_s;
	skip_unexpected_token = &skip_sep;
	while (*str)
	{
		tmp = skip_expected_token(str, 1);
		if (tmp)
			str = tmp;
		else 
		{
			skip_unexpected_token(str, 0);
			return (0);
		}
		swap(&skip_expected_token, &skip_unexpected_token);
	}
	return (1);
}

char	*g_exe_name;
t_list	*g_ptrs_lst;
int	main(int ac, char **av)
{
	g_exe_name = ft_strjoin(av[0], ": ");
char *valid_tests[50] =
{
	"sa\"\"lut",
	"\'\"\'salut",
	"sa\"\'\"lut",
	"cmd1 \'\"va\"&&||\'& cmd2||cmd2 etre|(cmd3>>file1)",
	"cmd1 \'\"va\"&&||\'& cmd2||cmd2 etre|(< cmd3 file1) ",
	"cmd1 \'\"va\"&&||\'& cmd2||cmd2 etre|(< cmd3 file1) ",
	"<cmd1 \'\"va\"&&||\'& cmd2||cmd2 etre|(cmd3>>file1)",
	"<cmd1",
	"(cmd) >file",
	"(cmd)>>file",
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
	"cmd1 \'\"va\"&&||\'& cmd2||cmd2 etre|(cmd3>>file1) &",
	"cmd1 \'\"va\"&&||\'& cmd2||cmd2 etre|(cmd3>>file1) &&",
	"cmd1 \'\"va\"&&||\'& cmd2||cmd2 etre|(cmd3>>file1) && ",
	"cmd1 (|cmd2)",
	"()",
	"cmd1 (| cmd2)",
	"cmd1 <<o (cmd2) (expect unexected token `(')",
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

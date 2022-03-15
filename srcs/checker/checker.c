/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:22:33 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/15 22:05:19 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

char	*check_fredi(char *str)
{
	str = skip_spaces(str);
	if (starts_by_f_redi(str))
	{
		str = starts_by_f_redi(str);
		str = skip_spaces(str);
		if (!check_after_fredi(str))
			return (NULL);
		return (skip_argument(str));
	}
	return (str);
}

//check that file redirections are terminated
//parentheses are considered as cmds
char	*skip_cmd_s(char *str)
{
	int		nb_arg;
	int		p;
	char	*tmp;

	nb_arg = 0;
	str = skip_spaces(str);
	p = 0;
	while (*str && !starts_by_sep(str) && *str != ')')
	{
		if (!check_p_in_cmd_s(&str, &p, &nb_arg))
			return (NULL);
		tmp = check_fredi(str);
		nb_arg += (skip_argument(str) != str || tmp);
		str = tmp;
		if (str == NULL)
			return (NULL);
		str = skip_argument(str);
		str = skip_spaces(str);
	}
	if (nb_arg != 0)
		return (str);
	return (NULL);
}

char	*skip_sep(char *str, int expected)
{
	char	*err_msg;
	char	*tmp;

	str = skip_spaces(str);
	tmp = str;
	str = starts_by_sep(str);
	if (str)
	{
		if (!expected || skip_spaces(str) - str == ft_strlen(str))
		{
			if (*tmp == '|' && tmp[1] == '|')
				unexpected_err_msg("||");
			if (*tmp == '|' && tmp[1] != '|')
				unexpected_err_msg("|");
			else
				unexpected_err_msg("&&");
		}
		return (str);
	}
	return (NULL);
}

int	should_exe_list(char *str)
{
	if (!quotes_closed(str) || !parentheses_closed(str))
		return (0);
	while (str)
	{
		if (skip_sep(str, 0))
			return (0);
		str = skip_cmd_s(str);
		if (str == NULL)
			return (0);
		str = skip_sep(str, 1);
	}
	return (1);
}

/*
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
	"<file1 | cmd1",
	"&",
	NULL
};
char *invalid_tests[50] =
{
//parentheses
	")(",
	"((((())salut))",
	"(((((\")\"))salut))",
//quotes
	"sa\"\'lut",
	"sa\"lut",
	"\'\'s\"alut",
//seps
	"cmd1 \'\"va\"&&||\'&&&&&&&&& cmd2||cmd2 etre|(cmd3>>file1)",
	"| cmd1 \'\"va\"&&||\'& cmd2||cmd2 etre|(cmd3>>file1) ",
	"cmd1 \'\"va\' cmd2|||||||||cmd2 etre|(cmd3>>file1)",
	"cmd1 \'\"va\"&&||\'& cmd2||cmd2 etre|(cmd3>>file1) &&",
	"cmd1 \'\"va\"&&||\'& cmd2||cmd2 etre|(cmd3>>file1) && ",
	"cmd1 (|cmd2)",
	"||",
	"|",
	"&&",
//sub shell
	"(cmd1)cmd2",
	"(cmd1) cmd2",
	"((cmd1)cmd2)",
	"(((((cmd1))cmd2)))",
	"cmd1 \'\"va\"&&||\'& cmd2||cmd2 etre|(cmd3>>file1) &",
	"cmd1 (| cmd2)",
	"cmd1 <<o (cmd2)",
	//considered invalid as parentheses are only for priorities
	"(cmd) >file",
	"(cmd)>>file",
	"(cmd)>>file",
//fredis
	"<",
	"><",
	"<>>",
	"<<<",
	"<<<<",
	"ls <<",
	"ls <<&&",
	"ls <<|",
	"ls <<||",
	"ls <<<<",
	">>>>",
	"ls >>||",
	"ls >>|",
	" <cmd>",
	"<>>",
//empty
	"()",
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:41:24 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/10 20:36:53 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	fredi(char *pathname, int flags, int stream)
{
	int	fd;

	fd = ft_open(pathname, flags);
	if (fd == -1)
		return (-1);
	ft_dup2(fd, stream);
	return (0);
}

void	here_doc(char *limit)
{
	char	*line;
	int	p_fds[2];

//printf("here_doc called on [%s]\n", limit);
	ft_pipe(p_fds);
	line = readline(">");
	while (line != NULL)
	{
		line[ft_strlen(line) - 1] = 0;	
		if (str_equal(line, limit))
		{
			free(line);
			break ;
		}
		line[ft_strlen(line)] = '\n';
		ft_write(p_fds[WRITE], line, ft_strlen(line));
		free(line);
		line = readline(">");
	}
	ft_dup2(p_fds[READ], READ);
	ft_close(p_fds[WRITE]);
	ft_close(p_fds[READ]);
}

char	*apply_here_docs(char *cmd_s)
{

}

char	*apply_infiles(char *cmd_s)
{
	char	*tmp;

	while ()
	{
		
	}
	return (tmp);
}
/*
char	*g_exe_name;
t_list	*g_ptrs_lst;

void	tester(char *str)
{
	printf("[%s]", str);
}

int	main()
{
	char *apply_f_redi_tests[50] =
	{
		"",
		"salut",
		"<<salut",
		"<salut",
		">>salut",
		">salut",
		"     <<     \tsalut     ",
		"     <\t      salut \t\t",
		"     >>                             salut",
		"     >          salut",
		">salut | aaaaaaa >>ewq",
		">salut | aaaaaaa >>e",
		">salut | aaaaaaa >>e ",
		">salut | aaaaaaa >>e ",
		"sa\"\"lut",
		"\'\"\'salut",
"sa\"\'\"lut",
"cmd1 \'\"va\"&&||\'& cmd2||cmd2 etre|(cmd3>>file1)",
	"cmd1 \'\"va\"&&||\'& cmd2||cmd2 etre|(cmd3>>file1) &",
	"cmd1 \'\"va\"&&||\'& cmd2||cmd2 etre|(< cmd3 file1) ",
	"cmd1 \'\"va\"&&||\'& cmd2||cmd2 etre|(< cmd3 file1) ",
	"<cmd1 \'\"va\"&&||\'& cmd2||cmd2 etre\'|(cmd3>>file1)\'",
	"<cmd1 \'\"va\"&&||\'& cmd2||cmd2 etre|(cmd3>>file1)",
	"<cmd1",
	"<file1 | cmd1",
	"<file1<cmd1",
		NULL
	};
	printf("tesing apply_f_redi_tests\n");
	for (int i = 0; apply_f_redi_tests[i]; i++)
	{
		printf("testing [%s]\n", apply_f_redi_tests[i]);
		printf("\"<<\" : ");
		apply_f_redi(apply_f_redi_tests[i], "<<", &tester);
		printf("\n\"<\" : ");
		apply_f_redi(apply_f_redi_tests[i], "<", &tester);
		printf("\n\">\" : ");
		apply_f_redi(apply_f_redi_tests[i], ">", &tester);
		printf("\n\">>\" : ");
		apply_f_redi(apply_f_redi_tests[i], ">>", &tester);
		printf("\n\n");
	}
	printf("testing here_doc\n");
	char	*here_doc_tests[50] = 
	{
		"<<asd",
		"<<z <<e , <<eqw",
		NULL
	};
	for (int i = 0; here_doc_tests[i]; i++)
	{
		printf("testing [%s]\n", here_doc_tests[i]);
		apply_f_redi(here_doc_tests[i], "<<", &here_doc);
	}
	printf("done\n");
}
//gcc file_redirections.c ../parsing_utils/*.c 
//-I ../parsing_utils -I../libft -L../libft -l ft -lreadline
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:41:24 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/14 16:04:30 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

//gerer EOF
int	*heredoc(char *limit, int *p_fds)
{
	char	*line;

	ft_pipe(p_fds);
	line = readline(">");
	while (line != NULL)
	{
		if (str_equal(line, limit))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(ft_strjoin(line, "\n"), p_fds[WRITE]);
		free(line);
		line = readline(">");
	}
	return (p_fds);
}

char	*apply_heredocs(char *cmd_s, int *p_fds)
{
	char	*tmp;

	tmp = NULL;
	while (strstr_q(cmd_s, "<<"))
	{
		if (tmp)
		{
			ft_close(p_fds[READ]);
			ft_close(p_fds[WRITE]);
		}
		tmp = strstr_q(cmd_s, "<<");
		cmd_s = tmp + 2;
		p_fds = heredoc(sub_argument(cmd_s), p_fds);
		cmd_s = skip_argument(cmd_s);
	}
	return (tmp);
}

int	fredi(char *pathname, int flags, int stream)
{
	int	fd;

	fd = ft_open(pathname, flags);
	if (fd == -1)
		return (-1);
	ft_dup2(fd, stream);
	return (0);
}

int	apply_infile(char *cmd_s, char **last_if)
{
	while (strchr_q(cmd_s, '<'))
	{
		cmd_s = strchr_q(cmd_s, '<') + 1;
		if (*cmd_s == '<')
		{
			cmd_s++;
			continue ;
		}
		*last_if = cmd_s - 1;
		if (fredi(sub_argument(cmd_s), READ_F, READ))
			return (1);
		cmd_s = skip_argument(cmd_s);
	}
	return (0);
}

/*
char	*g_exe_name;
t_list	*g_ptrs_lst;

int	main(int ac, char **av)
{
g_exe_name = av[0];
	printf("testing here_doc\n");
	char	*here_doc_tests[50] = 
	{
		"",
		"    \t         ",
		"<<asd",
		"<<  \tasd",
		"<<z <<e , <<eqw",
		NULL
	};
	int p_fds[2];
	ft_pipe(p_fds);
	for (int i = 0; here_doc_tests[i]; i++)
	{
printf("testing [%s]\n", here_doc_tests[i]);
printf
("last \"<<\" is at [%s]\n"
, apply_heredocs(here_doc_tests[i], p_fds[WRITE]));
	}
	printf("done\n");
	ft_exit(0);
}
//gcc file_redirections.c ../parsing_utils/ *.c 
//-I ../parsing_utils -I../libft -L../libft -l ft -lreadline
*/

/*
char	*apply_fredis(char *cmd_s, char *needle,  int flags,  int stream)
{
	char	*tmp;

	while (strstr_q(cmd_s, needle))
	{
		cmd_s = strstr_q(cmd_s, needle);
		if (!needle[1] && cmd_s[1] == *needle)
		{
			cmd_s++;
			continue ;
		}
		if ((fts[i])(sub_argument(cmd_s)))
			return (1);
		cmd_s = skip_argument(cmd_s);
	}
	return (cmd_s);
}
*/

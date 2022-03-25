/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:41:24 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/23 17:48:56 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

//gerer EOF
void	heredoc(char *limit, char first_c, int *p_fds, t_env env)
{
	char	*line;
	char	*expanded_line;

	set_signal_handler(&handle_sig_as_heredoc);
	line = get_line(">");
	while (line != NULL)
	{
		if (first_c != '\'' && first_c != '\"')
		{
			expanded_line = var_expand(line, *env.env, env.exit_status);
			free(line);
			line = expanded_line;
		}
		if (str_equal(line, limit) && (first_c == '\'' || first_c == '\"'))
			free(line);
		if (str_equal(line, limit))
			ft_exit(0);
		ft_putstr_fd(ft_strjoin(line, "\n"), p_fds[WRITE]);
		if (first_c == '\'' || first_c == '\"')
			free(line);
		line = get_line(">");
	}
	write_error(NULL, EOF_WARN, ft_strjoin(limit, EOF_WARN_END));
	ft_exit(0);
}

int	*launch_heredoc(char *limit, char first_c, int *p_fds, t_env env)
{
	pid_t	pid;

	ft_pipe(p_fds);
	pid = ft_fork();
	if (pid == 0)
		heredoc(limit, first_c, p_fds, env);
	if (ms_waitpid(pid))
		return (ft_close_p(p_fds), NULL);
	return (p_fds);
}

int	apply_heredocs(char **cmd_s, int *p_fds, t_env env)
{
	char	*tmp;

	tmp = NULL;
	if (!strstr_q(*cmd_s, "<<"))
	{
		*cmd_s = NULL;
		return (0);
	}
	while (strstr_q(*cmd_s, "<<"))
	{
		if (tmp)
			ft_close_p(p_fds);
		tmp = strstr_q(*cmd_s, "<<");
		*cmd_s = tmp + 2;
		p_fds = launch_heredoc(sub_argument(*cmd_s), **cmd_s, p_fds, env);
		if (p_fds == NULL)
			return (1);
		*cmd_s = skip_argument(*cmd_s);
	}
	return (0);
}

int	fredi(char *arg, t_env env, int flags, int stream)
{
	int		fd;
	char	*expanded_arg;
	long	expanded_len;

	arg = skip_spaces(arg);
	expanded_arg = sub_argument(arg);
printf("sub_arg = [%s]\n", expanded_arg);
	expanded_arg = var_expand(expanded_arg, *env.env, env.exit_status);
printf("expanded = [%s]\n", expanded_arg);
	expanded_len = skip_argument(expanded_arg) - expanded_arg;
	if (expanded_len != (long)ft_strlen(expanded_arg))
	{
		write_error(NULL, arg, "ambiguous redirect");
		return (1);
	}
	fd = ft_open(expanded_arg, flags);
	if (fd == -1)
		return (1);
	ft_dup2(fd, stream);
	return (0);
}

int	apply_infile(char *cmd_s, char **last_if, t_env env)
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
		if (fredi(sub(cmd_s, skip_argument(cmd_s)), env, READ_F, READ))
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

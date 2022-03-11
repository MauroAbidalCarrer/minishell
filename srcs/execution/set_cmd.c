/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:08:08 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/11 02:34:40 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	set_read(char *cmd_s)
{
	int	p_fds[2];
	char	*last_hd;
	char	*last_if;

	last_if = NULL;
	last_hd = apply_heredocs(cmd_s, p_fds);
	if (apply_infile(cmd_s, &last_if))
	{
		if (last_hd)
		{
			ft_close(p_fds[READ]);
			ft_close(p_fds[WRITE]);
		}
		return (1);
	}
//printf("las_hd = [%s]\n", last_hd);
//printf("las_if = [%s]\n", last_if);
//printf("last_hd = [%s], (!last_if) = %d, last_hd = %p,  last_if = %p, (last_hd > last_if) = %d\n", 
//last_hd, (!last_if), last_hd, last_if, (last_hd > last_if));
	if (last_hd && (!last_if || (last_hd > last_if)))
{printf("duping herdoc read on read_stream\n");
		ft_dup2(p_fds[READ], READ);
}
else{printf("did not dup heredoc read\n");}
	if (last_hd)
	{
		ft_close(p_fds[READ]);
		ft_close(p_fds[WRITE]);
	}
	return (0);
}

int	set_write(char *cmd_s)
{
	while (strchr_q(cmd_s, '>'))
	{
		cmd_s = strchr_q(cmd_s, '>') + 1;
		if (*cmd_s == '>')
			if (fredi(sub_argument(cmd_s), APPEND_F, WRITE))
				return (1);
		else if (fredi(sub_argument(cmd_s), CREAT_F, WRITE))
			return (1);
		cmd_s += (*cmd_s == '>');
		cmd_s = skip_argument(cmd_s);
	}
	return (0);
}

//no parenthees are possible here
void	set_acav(t_cmd *cmd, char *cmd_s)
{
	char	*tmp;
	int	i;

	cmd->ac = 0;
	tmp = cmd_s;
	while (*tmp)
	{
		tmp = skip_spaces(tmp);
		cmd->ac += (*tmp && !starts_by_f_redi(&tmp));
		tmp = skip_argument(tmp);
	}
	tmp = cmd_s;
	cmd->av = ft_malloc(sizeof(char *) * (cmd->ac + 1));
	cmd->av[cmd->ac] = NULL;
	i = 0;
	while (*tmp)
	{
		tmp = skip_spaces(tmp);
		if (*tmp && !starts_by_f_redi(&tmp))
			cmd->av[i++] = sub_argument(tmp);
		tmp = skip_argument(tmp);
	}
}

int ms_echo(int ac, char **av, char **env){return (0);}
int ms_cd(int ac, char **av, char **env){return (0);}
int ms_exit(int ac, char **av, char **env){return (0);}
int ms_pwd(int ac, char **av, char **env){return (0);}
int ms_export(int ac, char **av, char **env){return (0);}
int ms_unset(int ac, char **av, char **env){return (0);}
int ms_env(int ac, char **av, char **env){return (0);}

void	set_builtin(t_cmd *cmd)
{
	if (str_equal(cmd->av[0], "echo"))
		cmd->builtin = &ms_echo;
	else if (str_equal(cmd->av[0], "cd"))
		cmd->builtin = &ms_cd;
	else if (str_equal(cmd->av[0], "pwd"))
		cmd->builtin = &ms_pwd;
	else if (str_equal(cmd->av[0], "export"))
		cmd->builtin = &ms_export;
	else if (str_equal(cmd->av[0], "unset"))
		cmd->builtin = &ms_unset;
	else if (str_equal(cmd->av[0], "env"))
		cmd->builtin = &ms_env;
	else if (str_equal(cmd->av[0], "exit"))
		cmd->builtin = &ms_exit;
}

char	*get_path(char *name, char **env)
{
	char	*path;
	char	*paths;
	char	*err_msg;

	if (strchr(name, '/'))
			return (name);
	if (get_env_var("PATH", &paths, env))
		return (NULL);
	name = ft_strjoin("/", name);
	while (paths)
	{
		path = ft_substr(paths, 0, ilen_strchr(paths, ':'));
		path = ft_strjoin(path, name);
		if (access(path, F_OK) == 0)
			return (path);
		paths = strchr(paths, ':');
		paths += (paths != NULL);
	}
	ft_putstr_fd(ft_strjoin(name + (*name == '/'), CMD_NFOUND), 2);
	return (NULL);
}

char	*g_exe_name;
t_list	*g_ptrs_lst;
#include<stdio.h>
void	test_acav()
{
	char *acav_tests[50] =
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
		">salut  aaaaaaa >>ewq",
		">salut  aaaaaaa >>e",
		">salut  aaaaaaa >e ",
		">salut  aaaaaaa <<  e ",
		"sa\"\"lut",
		"\'\"\'salut",
"sa\"\'\"lut ca va ?",
"sa\"\'\"lut <ca >va ou i et <<toi >>?",
	"<cmd1",
	"<file1<cmd1",
		NULL
	};
	printf("testing set_acav\n");
	for (int i = 0; acav_tests[i]; i++)
	{
		printf("testing [%s]\n", acav_tests[i]);
		t_cmd cmd;
		set_acav(&cmd, acav_tests[i]);
		printf("ac = %d\n", cmd.ac);
		if (cmd.ac)
			printf("av = ");
		for (int j = 0; cmd.av[j]; j++)
			printf("[%s]", cmd.av[j]);
		printf("\n\n");
	}
}

void	test_path(char **env)
{
	char *path_tests[50] =
	{
		"cat",
		"ls",
		"nonexisent",
		"./a.out",
		NULL
	};

	printf("testing set_path\n");
	for (int i = 0; path_tests[i]; i++)
	{
		printf("testing [%s]\n", path_tests[i]);
		printf("path = [%s]\n\n", path_tests[i]);
		printf("\n");
	}
}

void	test_set_read(char *str)
{
	printf("testing [%s]\n", str);
	int	ret = set_read(str);
	printf("set_read = %d\n", ret);
	if (!ret)
	{
		char buff[21];
		ssize_t size = read(READ, buff, 20);
		if (size == -1)
			printf("read error\n");
		else
		{
			printf("read size = %ld\n", size);
			buff[size] = 0;
			printf("buff = [%s]\n", buff);
		}
	}
	printf("\n\n");
}

void	test_read()
{
	char	*tests[50] = 
	{
		"<set_cmd.c",
		"",
		"           \t          ",
		"<salut ",
		"      <           \t salut",
		"<'oui et toi'",
		"<\"oui et toi\"",
		"awhelWBEHK KQJwelkqwhbe lbe <\"oui et toi\"  qkwbqkwe ",
		"<salut<set_cmd.c<\"oui et toi\" klbakrbaoegbrrae",
		"<non_existent",
		"<NO_PERM",
		"wKJEVW LHFBAELHBE LWBAEO ",
		NULL
	};

	printf("testing infile\n");
	for (int i = 0; tests[i]; i++)
		test_set_read(tests[i]);
	printf("done\n");
}

void	test_heredoc(char *test)
{
/*
	char	*tests_with_heredocs[50] = 
	{
		"<<a",
		"<<a <set_cmd.c",
		"<< a   <set_cmd.c << asd",
		"<set_cmd.c",
		"<salut ",
		"      <           \t salut",
		"<'oui et toi'",
		"<\"oui et toi\"",
		"awhelWBEHK KQJwelkqwhbe lbe <\"oui et toi\"  qkwbqkwe ",
		"<salut<set_cmd.c<\"oui et toi\" klbakrbaoegbrrae",
		"<non_existent",
		"<NO_PERM",
		"wKJEVW LHFBAELHBE LWBAEO ",
		NULL
	};
*/
	printf("testing with heredocs\n");
	test_set_read(test);
}

int	main(int ac, char **av, char **env)
{
	g_exe_name = av[0];
	if (str_equal(av[1], "acav"))
		test_acav();
	else if (str_equal(av[1], "path"))
		test_path(env);
	else if (str_equal(av[1], "read"))
		test_read();
	else if (str_equal(av[1], "heredoc"))
		test_heredoc(av[2]);
	//else if (str_equal(av[1], "write"))
//		test_write();
	ft_exit(0);
}
//gcc set_cmd.c file_redirections.c ../parsing_utils/*.c
//-I ../parsing_utils/ -I ../libft -L../libft -lft -lreadline

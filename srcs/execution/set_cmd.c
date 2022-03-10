/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:08:08 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/10 01:51:08 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"


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

int	set_read(char *cmd_s)
{
	if (apply_f_redi(cmd_s, "<<", &here_doc))
		return (1);
	if (apply_f_redi(cmd_s, "<", &in_file))
		return (1);
	return (0);
}

int	set_path(t_cmd *cmd, char **env)
{
	char	*paths;
	char	*path;
	char	*err_msg;

	if (strchr(cmd->av[0], '/'))
	{
		cmd->path = cmd->av[0];
		return  (0);
	}
	if (!get_env_var("PATH", &paths, env))
	{
		cmd->path = ft_strjoin("/", cmd->av[0]);
		while (paths)
		{
			path = ft_substr(paths, 0, ilen_strchr(paths, ':'));
			path = ft_strjoin(path, cmd->path);
			if (access(path, F_OK) == 0)
			{
				cmd->path = path;
				return (0);
			}
			paths = strchr(paths, ':');
			paths += (paths != NULL);
		}
	}
	ft_putstr_fd(ft_strjoin(cmd->path + (*cmd->path == '/'), CMD_NFOUND), 2);
	return (1);
}

int	set_write(char *cmd_s)
{
	if (apply_f_redi(cmd_s, ">>", &append_file))
		return (1);
	if (apply_f_redi(cmd_s, "<", &out_file))
		return (1);
	return (0);
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
		t_cmd cmd;
		//cmd.av = {path_tests[i], NULL};
		cmd.av = ft_malloc(sizeof(char *));
		cmd.av[0] = path_tests[i];
		if (!set_path(&cmd, env))
			printf("path = [%s]\n\n", cmd.path);
		printf("\n");
	}
}

void	test_read()
{
	char *tests[50] =
	{
		"         <set_cmd.c<asdqweq       ",
		"",
		"             \t     ",
		"<set_cmd.c",
		"          <set_cmd.c",
		"          <      set_cmd.c",
		"         asdqweq       <set_cmd.c",
		"         <asdqweq       <set_cmd.c",
		"         <set_cmd.c<asdqweq       ",
		"         <set_cmd.c<set_cmd.c       ",
		NULL
	};

	printf("testing set_read just with \"<\"\n");
	for (int i = 0; tests[i]; i++)
	{
		printf("testing [%s]\n", tests[i]);
		int ret = set_read(tests[i]);
		printf("set_read = %d\n", ret);
		char buff[11];
		if (ret == 0)
		{
			ssize_t	nb_read = read(0, buff, 10);
			buff[nb_read] = 0;
			printf("read(10) = %ld, buff = [%s]\n", nb_read, buff);
		}
		printf("\n");
	}

	printf("\n\n\n");
	char	*tests_heredoc[50] =
	{
		" <set_cmd.c <<asd",
		"<<z<<asd",
		"<<'oui ca va'",
		NULL
	};
	printf("testing here_doc\n");
	for (int i = 0; tests_heredoc[i]; i++)
	{
		printf("testing [%s]\n", tests_heredoc[i]);
		int ret = set_read(tests_heredoc[i]);
		printf("set_read = %d\n", ret);
		char buff[11];
		if (ret == 0)
		{
			ssize_t	nb_read = read(0, buff, 10);
			buff[nb_read] = 0;
			printf("read(10) = %ld, buff = [%s]\n", nb_read, buff);
		}
	}
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
	//else if (str_equal(av[1], "write"))
//		test_write();
	ft_exit(0);
}
//gcc set_cmd.c file_redirections.c ../parsing_utils/*.c
//-I ../parsing_utils/ -I ../libft -L../libft -lft -lreadline

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_sys_calls.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 19:26:29 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/22 17:06:17 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

pid_t	ft_fork(void)
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		write_error(NULL, NULL);
		ft_exit(1);
	}
	return (child_pid);
}

int	ft_waitpid(pid_t pid)
{
	int	wstatus;

	if (waitpid(pid, &wstatus, WUNTRACED | WCONTINUED) == -1)
	{
		if (errno == EINTR)
			return (ft_waitpid(pid));
		write_error(NULL, NULL);
		ft_exit(1);
	}
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	if (WIFSIGNALED(wstatus))
		return (128 + WTERMSIG(wstatus));
	if (WIFSTOPPED(wstatus))
		return (128 + WSTOPSIG(wstatus));
	return (1);
}

/*
#include <stdio.h>
#include <stdlib.h>
char		*g_exe_name;
t_list	*g_ptrs_lst;
int	main(int ac, char **av, char **env)
{
	pid_t pid = ft_fork();
	if (pid)
	{
		printf("called\n");
		printf("%d\n", ft_waitpid(pid));
		printf("yass\n");
	}
	else
	{
		if (ac > 1)
			return (atoi(av[1]));
pause();
		char *yes[] = {"cat", NULL};
		execve("/usr/bin/cat", yes, env);
	}
}
*/

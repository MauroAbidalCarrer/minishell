/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:47:35 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/16 17:38:58 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_list	*g_ptrs_lst;
char	*g_exe_name;

//il faudra rajouter une fonciton "apply expansion avant exe_line
//line doit etre free avec free et non pas avec ft_free
int	main(int ac, char **av, char **env)
{
	char	*line;
	int	exit_status;

	exit_status = 0;
	(void)ac;
	if (strrchr(av[0], '/'))
		av[0] = strrchr(av[0], '/') + 1;
	g_exe_name = ft_strjoin(av[0], ": ");
	init_signal_handling();
	line = readline(g_exe_name);
	while (line != NULL)
	{
		if (should_exe_list(line))
			exit_status = exe_list(line, 0, env);
		free(line);
		line = readline(g_exe_name);
	}
	write(1, "exit\n", 5);
	ft_exit(0);
}

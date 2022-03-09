/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:47:35 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/08 15:57:30 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_list	*g_ptrs_lst;
char	*g_exe_name;

void	exec(char *line)
{
	printf("%s\n", line);
}

int	do_match(char const *str, char const *pattern);

//line doit etre free avec free et non pas avec ft_free
int	main(int ac, char **av)
{
//	char	*line;

	(void)ac;
	printf("%d\n", do_match(av[1], av[2]));
//	g_exe_name = ft_strjoin(av[0], ": ");
//	init_signal_handling();
//	line = readline(g_exe_name);
//	while (line != NULL)
//	{
//		if (should_exe_list(line))
//			exec(line);
//		free(line);
//		line = readline(g_exe_name);
//	}
//	write(1, "exit\n", 5);
	ft_exit(0);
}

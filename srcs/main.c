/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:47:35 by maabidal          #+#    #+#             */
/*   Updated: 2022/02/22 20:46:19 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_list	*g_ptrs_lst;
char	*g_exe_name;

void	exec(void)
{
}

int	main(int ac, char **av)
{
	char	*line;

	(void)ac;
	g_exe_name = av[0];
	init_signal_handling();
	line = readline(PROMPT);
	while (line != NULL)
	{
		printf("%s\n", line);
		free(line);
		line = readline(PROMPT);
	}
	write(1, "exit\n", 5);
}

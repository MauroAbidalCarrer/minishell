/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:47:35 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/04 15:56:18 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_list	*g_ptrs_lst;
char	*g_exe_name;

void	exec(void)
{
}

int	ms_export(int ac, char **av, char ***env);

int	main(int ac, char **av, char **env)
{
//	char	*line;

	init_signal_handling();
//	line = readline(PROMPT);
//	while (line != NULL)
//	{
//		printf("%s\n", line);
//		free(line);
//		line = readline(PROMPT);
//	}
	ms_export(ac, av, &env);
	printf("------------------------------\n");
	ms_export(1, av, &env);
	write(1, "exit\n", 5);
}

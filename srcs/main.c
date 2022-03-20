/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:47:35 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/20 18:18:42 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_list	*g_ptrs_lst;
char	*g_exe_name;

char	*get_line(char *prompt)
{
	char	*tmp;

	if (isatty(READ))
		return (readline(prompt));
	tmp = get_next_line(READ);
	if (tmp && ft_strlen(tmp) && tmp[ft_strlen(tmp) - 1] == '\n')
		tmp[ft_strlen(tmp) - 1] = 0;
	return (tmp);
}

char	*set_exename(char *av0)
{
	if (strrchr(av0, '/'))
		av0 = strrchr(av0, '/') + 1;
	av0 = ft_strjoin(av0, ": ");
	return (av0);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	char	*prompt;
	int		exit_status;

	(void) exit_status;
	g_exe_name = set_exename(av[0]);
	exit_status = 0;
	(void)ac;
	set_signal_handler(&handle_signal);
	prompt = "";
	if (isatty(READ))
		prompt = g_exe_name;
	line = get_line(prompt);
	while (line != NULL)
	{
		add_history(line);
		if (should_exe_list(line))
			exit_status = exe_list(line, 0, &env);
		free(line);
		line = get_line(prompt);
	}
	write(1, "exit\n", 5);
	ft_exit(0);
}

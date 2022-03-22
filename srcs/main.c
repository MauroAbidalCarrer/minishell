/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:47:35 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/22 17:05:08 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_list	*g_ptrs_lst;

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

char	*set_exename_n_prompt(char *av0)
{
	if (strrchr(av0, '/'))
		av0 = strrchr(av0, '/') + 1;
	av0 = ft_strjoin(av0, ": ");
	write_error(NULL, av0);
	return (av0);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	char	*prompt;
	int		exit_status;

	(void)ac;
	exit_status = 0;
	set_signal_handler(&handle_signal);
	prompt = set_exename_n_prompt(av[0]);
	if (!isatty(READ))
		prompt = "";
	line = get_line(prompt);
	while (line != NULL)
	{
		add_history(line);
		if (should_exe_list(line))
			exit_status = exe_list(line, 0, &env);
		free(line);
		line = get_line(prompt);
	}
	if (isatty(READ))
		write(1, "exit\n", 5);
	ft_exit(0);
}

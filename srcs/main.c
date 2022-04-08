/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:47:35 by maabidal          #+#    #+#             */
/*   Updated: 2022/04/08 18:17:35 by maabidal         ###   ########.fr       */
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

char	*set_exename(char *av0)
{
	if (ft_strrchr(av0, '/'))
		av0 = ft_strrchr(av0, '/') + 1;
	av0 = ft_strjoin(av0, ": ");
	write_error(av0, NULL, NULL);
	return (av0);
}

t_env	set_env(char ***env)
{
	t_env	ms_env;

	ms_env.exit_status = 0;
	ms_env.env = env;
	return (ms_env);
}

void	handle_input(t_env env, char *exename)
{
	char	*line;
	char	*prompt;
	int		*r_pipes;

	prompt = "";
	if (isatty(READ))
		prompt = exename;
	line = get_line(prompt);
	while (line != NULL)
	{
		add_history(line);
		if (should_exe_list(line, exename))
		{
			r_pipes = mk_heredocs(line, env);
			if (r_pipes != NULL)
			{
				exe_list(line, 0, &env, &r_pipes);
				while (*r_pipes != -1)
					ft_close(*(r_pipes++));
			}
		}
		free(line);
		line = get_line(exename);
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	set_signal_handler(&handle_signal);
	handle_input(set_env(&env), set_exename(av[0]));
	if (isatty(READ))
		write(1, "exit\n", 5);
	ft_exit(0);
}

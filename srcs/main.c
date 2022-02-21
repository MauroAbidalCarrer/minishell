/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:47:35 by maabidal          #+#    #+#             */
/*   Updated: 2022/02/21 12:21:41 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	exec(void)
{
}

int	main(int ac, char **av, char **env)
{
	char	*line;

	(void) ac;
	(void) av;
	(void) env;
	line = readline(PROMPT);
	while (line != NULL)
	{
		printf("%s\n", line);
		free(line);
		line = readline(PROMPT);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:47:35 by maabidal          #+#    #+#             */
/*   Updated: 2022/02/21 12:30:33 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	exec(void)
{
}

int	main(int ac, char **av)
{
	char	*line;

	(void) ac;
	(void) av;
	line = readline(PROMPT);
	while (line != NULL)
	{
		printf("%s\n", line);
		free(line);
		line = readline(PROMPT);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:47:35 by maabidal          #+#    #+#             */
/*   Updated: 2022/02/18 15:02:11 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int ac, char **av, char **env)
{
	char	*line;

	line = readline("salut: ");
	while (line != NULL)
	{
		printf("%s\n", line);
		free(line);
		line = readline("salut: ");
	}
}

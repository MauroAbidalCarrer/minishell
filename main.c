/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:47:35 by maabidal          #+#    #+#             */
/*   Updated: 2022/02/18 14:54:42 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

       #include <stdio.h>
       #include <readline/readline.h>
       #include <readline/history.h>

int	 main()
{
	char *line = readline("salut: ");
	while (line != NULL)
	{
		//parse
		//exec
		printf("%s\n", line);
		free(line);
		line = readline("salut: ");
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 19:00:03 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/09 16:46:06 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>


int	main(int ac, char **av)
{

}

/*
int	main(int ac, char **av)
{
	int	saved_write = dup(1);
	printf("saved_write = %d\nClosing 1\n", saved_write);
	//close(1);
	int	fd = open(av[1], O_RDONLY);
	dup2(fd, 1);
	close(fd);
	write(saved_write, "trying to write\n", 16);
	dup2(saved_write, 1);
	printf("restored write\n");
	close(saved_write);
}
*/

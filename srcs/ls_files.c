/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_files.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:17:52 by jmaia             #+#    #+#             */
/*   Updated: 2022/02/21 12:18:31 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>

int	main(void)
{
	struct dirent	*entry;
	DIR				*dir;

	dir = opendir(".");
	entry = readdir(dir);
	while (entry)
	{
		printf("%s\n", entry->d_name);
		entry = readdir(dir);
	}
}

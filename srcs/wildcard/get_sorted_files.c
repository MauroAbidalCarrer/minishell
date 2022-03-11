/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sorted_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 15:22:13 by jmaia             #+#    #+#             */
/*   Updated: 2022/03/11 15:37:13 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

t_list	*get_sorted_files(DIR *dir)
{
	struct dirent	*dirent;
	t_list			*lst;
	t_list			*cur;

	lst = 0;
	dirent = readdir(dir);
	while (dirent)
	{
		cur = ft_lstnew(ft_strdup(dirent->d_name));
		if (!cur || !cur->content)
			break ;
		ft_lstadd_back(&lst, cur);
		dirent = readdir(dir);
	}
	ft_lstsort(lst, (int (*)(void *, void *))(&ft_strcmp));
	if (errno)
		ft_lstclear(&lst, &free);
	return (lst);
}

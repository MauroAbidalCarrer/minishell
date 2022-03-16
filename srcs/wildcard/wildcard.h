/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:27:45 by jmaia             #+#    #+#             */
/*   Updated: 2022/03/16 16:25:13 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

# include <dirent.h>
# include <sys/types.h>

# include "libdynamic_buffer.h"
# include "libft.h"

int			do_match(char const *str, char const *pattern);
t_list		*get_sorted_files(DIR *dir);
char		*wild_it(char const *pattern);
char const	*get_next_word(char const *cur_word);

#endif

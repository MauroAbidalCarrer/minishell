/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:27:45 by jmaia             #+#    #+#             */
/*   Updated: 2022/03/11 14:04:25 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

# include <dirent.h>
# include <sys/types.h>

# include "libdynamic_buffer.h"
# include "libft.h"

int		do_match(char const *str, char const *pattern);
char	*wild_it(char const *pattern);

#endif

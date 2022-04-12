/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:27:45 by jmaia             #+#    #+#             */
/*   Updated: 2022/04/12 22:22:44 by jmaia            ###   ########.fr       */
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
char		*wild_it(char *pattern);
int			wild_word(char const *cur_word, t_dynamic_buffer *buffer);
char		*get_next_word(char *cur_word);

int			test_if_wildcard_ambiguous(char *pattern);
void		append_full_quoted_word(t_dynamic_buffer *buffer, char *word);

typedef enum e_redirection_status
{
	NOT_IN_REDIRECTION,
	BEFORE_WORD,
	IN_WORD
}	t_redirection_status;

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 18:27:44 by maabidal          #+#    #+#             */
/*   Updated: 2022/04/08 18:07:18 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include<unistd.h>
# include<limits.h>
# include<stdlib.h>
# include "libft.h"
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

void	*free_prev(char **prev_add);
char	*get_next_line(int fd);
char	*join(char *s1, char *s2);
char	*r_join(char *s1, char *s2, size_t len);
char	*alloc_line(size_t len);
size_t	n_index(char *str);
char	*get_next_line_heredoc();
#endif

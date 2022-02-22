/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_calls.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 15:46:06 by maabidal          #+#    #+#             */
/*   Updated: 2022/02/22 22:33:13 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYS_CALLS_H
# define SYS_CALLS_H
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include "libft.h"
# include <string.h>
# define CREAT_M 420
# define CREAT_F  577
# define APPEND_F  1089

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

extern char		*g_exe_name;
extern t_list	*g_ptrs_lst;
void	*ft_malloc(size_t size);
void	ft_free(void *ptr);

int		ft_fork(void);
void	ft_exit(int status);

int		ft_open(const char *pathname, int flags);
void	ft_close(int fd);
void	ft_pipe(int pipefd[2]);
void	ft_dup2(int oldfd, int newfd);

void	write_error(char *append_msg);
int		ft_write(int fd, const void *buf, size_t count);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:10:03 by jmaia             #+#    #+#             */
/*   Updated: 2022/03/29 19:21:05 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLING_H
# define SIGNAL_HANDLING_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>

# include "signal.h"
# include "libft.h"

typedef void	(*t_sig_handler)(int, siginfo_t *, void *);
void	set_signal_handler(t_sig_handler sig_handler);
void	set_signal_handler_as_parent(void);
void	handle_signal(int sig, siginfo_t *info, void *ucontext);
void	handle_sig_as_parent(int sig, siginfo_t *info, void *ucontext);
void	handle_sig_as_heredoc(int sig, siginfo_t *info, void *ucontext);

#endif

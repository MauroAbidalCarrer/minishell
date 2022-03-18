/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:10:03 by jmaia             #+#    #+#             */
/*   Updated: 2022/03/18 20:06:56 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLING_H
# define SIGNAL_HANDLING_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>

# include "signal.h"

typedef void (*t_sig_handler)(int, siginfo_t *, void *);
void	set_signal_handler(t_sig_handler sig_handler);
void	handle_signal(int sig, siginfo_t *info, void *ucontext);
void	handle_sig_as_parent(int sig, siginfo_t *info, void *ucontext);

#endif

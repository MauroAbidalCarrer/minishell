/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:58:10 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/22 19:49:29 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>

typedef struct s_env
{
	char	***env;
	int		exit_status;
}	t_env;

# include "get_next_line.h"
# include "libft.h"
# include "signal_handling.h"
# include "checker.h"
# include "var_expand.h"
# include "execution.h"

#endif

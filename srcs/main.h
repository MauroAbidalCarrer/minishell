/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:58:10 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/17 17:50:43 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>

# include "get_next_line.h"
# include "libft.h"
# include "signal_handling.h"
# include "checker.h"
# include "execution.h"

typedef struct s_env
{
	char	***env;
	int		exit_status;
}	t_env;

int	set_env_var(char const *key, char const *value);
int	delete_env_var(char const *key);

#endif

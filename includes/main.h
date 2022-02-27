/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:58:10 by maabidal          #+#    #+#             */
/*   Updated: 2022/02/27 15:18:17 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include "libft.h"
# include "signal_handling.h"
# ifndef PROMPT
#  define PROMPT "minishell: "
# endif

int	get_env_var(char const *str, char **dest, char **env);
int	set_env_var(char const *key, char const *value);

#endif

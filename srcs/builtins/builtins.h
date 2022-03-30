/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:43:27 by jmaia             #+#    #+#             */
/*   Updated: 2022/03/30 14:24:20 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <dirent.h>
# include <stdlib.h>
# include <sys/types.h>

# include "libft.h"
# include "libdynamic_buffer.h"

# include "env_utils.h"
# include "main.h"

int		ms_echo(int ac, char **av, t_env env);
int		ms_cd(int ac, char **av, t_env env);
int		ms_pwd(int ac, char **av, t_env env);
int		ms_export(int ac, char **av, t_env env);
int		ms_unset(int ac, char **av, t_env env);
int		ms_env(int ac, char **av, t_env env);
int		ms_exit(int ac, char **av, t_env env);

char	*escape_quote_and_backslash(char *var);
char	*quote_value(char *var);
int		append_and_quote_str(t_dynamic_buffer *buffer, char *str);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:43:27 by jmaia             #+#    #+#             */
/*   Updated: 2022/02/22 21:21:56 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdlib.h>

# include "libft.h"

int	ms_echo(int ac, char **av);
int	ms_cd(int ac, char **av);
int	ms_pwd(int ac, char **av);
int	ms_export(int ac, char **av);
int	ms_unset(int ac, char **av);
int	ms_env(int ac, char **av);
int	ms_exit(int ac, char **av);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:44:11 by jmaia             #+#    #+#             */
/*   Updated: 2022/03/23 16:50:06 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VAR_EXPAND_H
# define VAR_EXPAND_H

# include <stdlib.h>

# include "libdynamic_buffer.h"

# include "main.h"

char	*get_line(char *prompt);
char	*var_expand(char *pattern, char **env, int status_code);

#endif

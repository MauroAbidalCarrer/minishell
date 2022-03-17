/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 10:57:57 by jmaia             #+#    #+#             */
/*   Updated: 2022/03/17 14:04:40 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_UTILS_H
# define ENV_UTILS_H

# include <stdlib.h>

# include "libft.h"

int	get_env_var(char *key, char **dst, char **env);
int	set_env_var(char *key, char *value, char ***env);
int	delete_env_var(char *key, char ***env);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:27:01 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/25 16:29:08 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

//little headerto declare the env struct, the norm doesn't allow structs to
//be defined before libraries
typedef struct s_env
{
	char	***env;
	int		exit_status;
}	t_env;

#endif

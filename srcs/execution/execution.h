/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:19:31 by maabidal          #+#    #+#             */
/*   Updated: 2022/02/23 15:23:06 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
typedef struct cmd
{
	char	*path;
	char	**av;
	int		ac;
}	t_cmd;
# define CREAT_M 644
# define CREAT_F 577
# define APPEND_F 1089

#endif

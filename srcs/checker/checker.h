/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 19:07:56 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/06 00:43:23 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H
# include "libft.h"

int	starts_by_f_redi(char **str);
int	starts_by_sep(char **str);
int	check_quotes(char *str);
int	check_parentheses(char *str);
int	starts_by_f_redi(char **str);
int	to_ending_par(char *str);
int	should_exe_list(char *str);
#endif

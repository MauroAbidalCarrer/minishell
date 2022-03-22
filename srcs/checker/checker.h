/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 19:07:56 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/22 17:21:02 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H
# include "libft.h"
# include "parsing_utils.h"
# define ERR_PRE "syntax error near unexpected token `"

void	err_msg(char *err, char *exename);

int		check_p_in_cmd_s(char **str, int *p, int *nb_arg, char *exename);
int		check_after_fredi(char *str, char *exename);

char	*skip_sep(char *str, int expcted, char *exename);

int		parentheses_closed(char *str, char *exename);
int		quotes_closed(char *str);

int		should_exe_list(char *str, char *exename);
#endif

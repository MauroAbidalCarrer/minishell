/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 19:07:56 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/14 18:17:12 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H
# include "libft.h"
# include "parsing_utils.h"
# define ERR_PRE "syntax error near unexpected token `"

char	*skip_sep(char *str, int expcted);
int		check_parentheses(char *str);
int		check_quotes(char *str);

typedef char	(*skip_token)(char *, int);

int		should_exe_list(char *str);
#endif

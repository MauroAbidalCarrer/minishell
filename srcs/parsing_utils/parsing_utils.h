/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:53:49 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/15 16:39:43 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_UTILS_H
# define PARSING_UTILS_H
# include "libft.h"

char	*starts_by_sep(char *str);
char	*starts_by_f_redi(char *str);
char	*to_ending_par(char *str);

char	*strstr_q(char *str, char *needle);
char	*strchr_q(char *str, char needle);
char	*strchr_qp(char *str, char needle);
char	*strstr_qp(char *str, char *needle);
char	*skip_quotes(char *str);

char	*sub_argument(char *str);
char	*skip_argument(char *str);
int		get_env_var(char *key, char **dst, char **env);
#endif

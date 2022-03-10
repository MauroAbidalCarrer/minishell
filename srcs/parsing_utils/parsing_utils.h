/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:53:49 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/09 17:52:52 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_UTILS_H
# define PARSING_UTILS_H
# include "libft.h"

int		starts_by_sep(char **str);
int		starts_by_f_redi(char **str);
int		to_ending_par(char *str);

char	*strstr_q(char *str, char *needle);
char	*skip_quotes(char *str);

char	*sub_argument(char *str);
char	*skip_argument(char *str);
int	get_env_var(char *key, char **dst, char **env);
#endif

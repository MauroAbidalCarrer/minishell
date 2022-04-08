/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:44:11 by jmaia             #+#    #+#             */
/*   Updated: 2022/04/08 13:47:14 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VAR_EXPAND_H
# define VAR_EXPAND_H

# include <stdlib.h>

# include "libdynamic_buffer.h"

# include "main.h"

typedef enum e_heredoc_status
{
	NOT_IN_HEREDOC,
	BEFORE_DELIMITER,
	IN_DELIMITER
}	t_heredoc_status;

typedef enum e_ambiguous_state
{
	HAS_NO_NORMAL_CHARACTERS,
	HAS_NORMAL_CHARACTERS,
	IS_AMBIGUOUS
}	t_ambiguous_state;

char	*get_line(char *prompt);

char	*var_expand(char *pattern, t_env env);
int		process_pattern(t_dynamic_buffer *buffer, t_env env, char *pattern);
char	*is_ambiguous(char *str, t_env env, t_heredoc_status heredoc_status);
int		append_quoted_str_and_move(t_dynamic_buffer *d_buffer, char **str);
int		append_var_and_move(t_dynamic_buffer *buffer, char **cur_c,
			t_env env, int in_dquote);

int		append_var_and_move2(t_dynamic_buffer *buffer, t_env env,
			char **cur_c, int in_dquote);
int		is_almost_valid_char_for_name(char c);
int		append_str(t_dynamic_buffer *buffer, char *str);
void	update_heredoc_status(char *str, t_heredoc_status *heredoc_status);

void	update_ambiguous_state(t_ambiguous_state *ambiguous_state,
			char **cur, t_env env);

char	*var_expand_in_heredoc(char *pattern, t_env env);

void	append_exit_status(t_dynamic_buffer *buffer, t_env env);
void	append_env_var_and_move_in_heredoc_mode(t_dynamic_buffer *buffer,
			char **pattern, t_env env);

int		append_and_quote_str(t_dynamic_buffer *buffer, char *str);

#endif

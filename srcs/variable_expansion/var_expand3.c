/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 12:15:54 by jmaia             #+#    #+#             */
/*   Updated: 2022/04/07 12:17:44 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "var_expand.h"

void	update_ambiguous_state(t_ambiguous_state *ambiguous_state,
				char **cur, t_env env)
{
	t_dynamic_buffer	buffer;
	unsigned long		i;

	if (**cur != '$')
	{
		*ambiguous_state = HAS_NORMAL_CHARACTERS;
		return ;
	}
	buffer = get_buffer(sizeof(char));
	append_var_and_move(&buffer, cur, env, 0);
	i = 0;
	while (i < buffer.i && *ambiguous_state != IS_AMBIGUOUS)
	{
		if (ft_isspace(((char *)buffer.buffer)[i]))
			*ambiguous_state = IS_AMBIGUOUS;
		else
			*ambiguous_state = HAS_NORMAL_CHARACTERS;
		i++;
	}
	ft_free(buffer.buffer);
}

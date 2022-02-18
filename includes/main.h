/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:58:10 by maabidal          #+#    #+#             */
/*   Updated: 2022/02/18 16:40:58 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# ifndef PROMPT
#  define PROMPT "minishell: "
# endif

typedef struct s_block
{

}	t_block;

enum block_operator
{

}

typedef struct s_instruction
{
	
}	t_intruction;

int	get_env_var(char *key, char **dst, char **env);
void	exec(/*?*/);

#endif

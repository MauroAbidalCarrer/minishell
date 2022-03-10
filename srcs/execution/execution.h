/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:17:47 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/10 16:30:02 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "libft.h"
# include "parsing_utils.h"
# define READ 0
# define WRITE 1
# define CREAT_F 577
# define APPEND_F 1089 
# define CMD_NFOUND ": command not found\n"


typedef struct cmd
{
	char	*path;
	char	**av;
	int		ac;
	
}	t_cmd;
typedef (*t_builtin)(int ac, char **av, char **env);
int	exe_cmd_s(char *cmd_s, int is_child, char **env);

void	set_acav(t_cmd *cmd, char *cmd_s);
void	set_builtin(t_cmd *cmd);
int	set_path(t_cmd *cmd, char **env);

//fredi = file redirection
int	apply_fredis(char *cmd_s);
#endif

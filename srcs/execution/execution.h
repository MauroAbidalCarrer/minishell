/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:17:47 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/10 20:11:05 by maabidal         ###   ########.fr       */
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
# define READ_F O_RDONLY
# define CMD_NFOUND ": command not found\n"

typedef (*t_builtin)(int ac, char **av, char **env);
typedef struct cmd
{
	char	*path;
	char	**av;
	int		ac;
	t_builtin	builtin;
}	t_cmd;

int		exe_cmd_s(char *cmd_s, int is_child, char *paths);

int		set_read(char *cmd_s);
int		set_write(char *cmd_s);
void	set_acav(char *cmd_s);
void	set_builtin(t_cmd *cmd);
int		set_path(t_cmd *cmd, char *paths);

char	*apply_here_docs(char cmd_s, int p_write);
char	*apply_fredis(char *cmd_s, int flags,  int stream);
#endif
//here_doc
//in_files
//apply furthest between here_doc and in_files
//out files
//command

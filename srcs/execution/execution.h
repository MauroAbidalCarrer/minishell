/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:17:47 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/11 12:57:34 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include <readline/readline.h>
# include "libft.h"
# include "parsing_utils.h"
# define READ 0
# define WRITE 1
# define CREAT_F 577
# define APPEND_F 1089 
# define READ_F O_RDONLY
# define CMD_NFOUND ": command not found\n"
# define PERM_DEN ": permissioin denied\n"

int		exe_list(char *list, int is_child, char **env);

typedef struct s_pipe_data
{
	pid_t	pid;
	int		p_read;
	int		p_fds[2];
	char	*line;
}	t_p_data;

typedef int	(*t_builtin)(int ac, char **av, char **env);
typedef struct cmd
{
	char		*path;
	char		**av;
	int			ac;
	t_builtin	builtin;
}	t_cmd;

int		exe_cmd_s(char *cmd_s, int is_child, char **env);

int		set_read(char *cmd_s);
int		set_write(char *cmd_s);
void	set_acav(t_cmd *cmd, char *cmd_s);
void	set_builtin(t_cmd *cmd);
char	*get_path(char *name, char **env);

char	*apply_heredocs(char *cmd_s, int *p_fds);
int		apply_infile(char *cmd_s, char **last_if);

int		fredi(char *pathname, int flags, int stream);
#endif
//read
//	here_doc
//	in_files
//	apply furthest between here_doc and in_files
//write
//	out files
//command
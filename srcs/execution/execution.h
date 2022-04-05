/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:17:47 by maabidal          #+#    #+#             */
/*   Updated: 2022/04/05 15:53:02 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "main.h"
# include "libft.h"

# include "parsing_utils.h"
# include "builtins.h"

# define READ 0
# define WRITE 1
# define CREAT_F 577
# define APPEND_F 1089 
# define READ_F O_RDONLY
# define CMD_NFOUND ": command not found\n"
# define PERM_DEN ": permissioin denied\n"
# define EOF_WARN "warning: here-document delimited by end-of-file (wanted `"
# define EOF_WARN_END "')"

int		exe_list(char *list, int is_child, t_env env, int **r_pipes);
int		ms_waitpid(pid_t pid);

typedef struct s_pipe_data
{
	pid_t	pid;
	int		p_read;
	int		p_fds[2];
	char	*line;
	int		is_child;
}	t_p_data;

typedef int	(*t_builtin)(int ac, char **av, t_env env);
typedef struct cmd
{
	char		*path;
	char		**av;
	int			ac;
	t_builtin	builtin;
}	t_cmd;

int		exe_cmd_s(char *cmd_s, int is_child, t_env env, int **r_pipes);

int		set_read(char *cmd_s, int **r_pipes, int is_child);
int		set_write(char *cmd_s);
void	set_acav(t_cmd *cmd, char *cmd_s);
void	set_builtin(t_cmd *cmd);
char	*get_path(char *name, char **env);

int		*mk_heredocs(char *list, t_env env);

int		fredi(char *arg, int flags, int stream);
#endif

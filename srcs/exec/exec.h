/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:13:56 by atudor            #+#    #+#             */
/*   Updated: 2024/03/04 15:13:58 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../../srcs/env/env.h"

//Executor
typedef struct s_xdata
{
	struct s_cmd	**cmd_arr;
	pid_t			*pid;
}	t_xdata;

typedef struct s_xcmd
{
	int		cmd_id;
	int		nr_cmds;
	char	**cmd;
	int		builtin;
	char	*path;
	int		nr_redir_out;
	int		nr_redir_in;
	int		nr_heredoc;
	int		nr_append;
	char	**infile;
	int		fd_in;
	char	**outfile;
	int		fd_out;
	char	**append;
	int		fd_append;
	int		pipefd[2];
	pid_t	*pid;
}	t_xcmd;

int		ft_strcmp(const char *line, const char *s);
int		changedir(char	**cmd);
void	execute_command(char **env, char *command);
void	exec_cmd(char **env, char *command);

void	fill_path(t_xcmd *xcmd);
char	*access_path(char *argv);

// exec
void	parse_and_exec(char *s, t_env *env);
void	pipe_error(int *pipefd);

// init_xcmd
void	fill_redirs(t_xcmd *xcmd, t_redir_token *parse_redir);
void	fill_cmd(char ***xcmd, t_single_cmd *cmd);
void	fill(t_xcmd *xcmd, t_command *cmd, int nr_cmds, pid_t *pid);
t_xcmd	**allocate_and_fill(t_command *cmd, int nr_cmds);
t_xcmd	**init_exe_cmd(t_command *cmd);

// init_utils
int		count_cmds(t_command *cmd);
void	count_redirs(t_xcmd *xcmd, t_redir_token *parse_redir);
int		check_builtin(char **xcmd);

// redirections



#endif
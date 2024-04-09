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
# include "libft/libft.h"

//Executor
typedef struct s_xdata
{
	struct s_cmd	**cmd_arr;
	pid_t			*pid;
}	t_xdata;

typedef struct s_xcmd
{
	int		cmd_id;
	int		nr_of_cmds;
	char	**cmd;
	int		builtin;
	char	*path;
	int		nr_redir_out;
	int		nr_redir_in;
	int		nr_heredoc;
	int		nr_append;
	char	**filename_in;
	int		fd_in;
	char	**filename_out;
	int		fd_out;
	char	**filename_append;
	int		fd_append;
	int		pipefd[2];
	pid_t	*pid;
}	t_xcmd;

int		ft_strcmp(const char *line, const char *s);
int		changedir(char	**cmd);
void	execute_command(char **env, char *command);
void	exec_cmd(char **env, char *command);
t_xcmd	**init_exe_cmd(t_command *cmd);
void	fill_cmd(char ***xcmd, t_single_cmd *cmd);
void	fill_path(t_xcmd *xcmd);
void	fill_redir(t_xcmd *xcmd, t_single_cmd *cmd);
int	check_builtin(char **xcmd);
char	*access_path(char *argv);
void	count_redirs(t_xcmd *xcmd, t_redir_token *parse_redir);
void	fill_redirs(t_xcmd *xcmd, t_redir_token *parse_redir);
void	parse_and_exec(char *s);

// init_xcmd
void more_init(t_xcmd *xcmd, t_command *cmd, int i, int nr_cmds, pid_t *pid);


#endif

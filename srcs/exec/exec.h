/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:13:56 by atudor            #+#    #+#             */
/*   Updated: 2024/04/19 18:41:50 by pfontenl         ###   ########.fr       */
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
# include "../../inc/env.h"
# include "../../inc/minishell.h"
# include "../built-ins/builtins.h"

//Executor
typedef struct s_data
{
	t_env			*env_list;
	t_export		*export_list;
}	t_data;

typedef struct s_xcmd
{
	int				cmd_id;
	int				nr_cmds;
	char			**cmd;
	char			**expanded_full;
	int				builtin;
	char			*path;
	int				nr_redir_out;
	int				nr_redir_in;
	t_redir_token	*redirs;
	int				fd_in;
	int				fd_o;
	int				nr_heredoc;
	int				pipefd[2];
	pid_t			*pid;
	int				exit_status;
}	t_xcmd;

int		ft_strcmp(const char *line, const char *s);
int		changedir(char	**cmd);
void	execute_command(char **env, char *command);
void	exec_cmd(char **env, char *command);

void	fill_path(t_xcmd *xcmd);

// exec
void	parse_and_exec(char *s, t_data *data);
void	redir_and_execute(t_xcmd **cmd, t_data *data);

// exec_utils
void	pipe_error(int *pipefd);

// pipexstuff
char	**find_path(char **env, char *s);
void	execution(t_data *data, t_xcmd *cmd);

// init_xcmd
void	fill_redirs(t_xcmd *xcmd, t_redir_token *parse_redir);
void	fill_cmd(char ***xcmd, t_single_cmd *cmd);
void	fill(t_xcmd *xcmd, t_single_cmd *cursor, int nr_cmds, pid_t *pid);
t_xcmd	**allocate_and_fill(t_command *cmd, int nr_cmds);
t_xcmd	**init_exe_cmd(t_command *cmd);

// init_utils
int		count_cmds(t_command *cmd);
void	count_args(t_text_token *text, char ***args);
void	allocate_cmd_and_pid(t_xcmd **xcmd, int nr_cmds);
void	count_redirs(t_xcmd *xcmd, t_redir_token *parse_redir);
int		check_builtin(char **xcmd);

// redirections
void	redirections(t_xcmd **cmd, int i, int *flag);

char	**get_cmd_array(t_single_cmd *cmd);

// cd
void	ft_cd(t_xcmd *cmd, t_env *env_list);

// echo
void	ft_echo(t_xcmd *cmd);

// env

void	ft_env(t_xcmd *cmd, t_data *data);

// exit
void	ft_exit(t_xcmd *xcmd, int *flag);

// export
void	ft_export(t_xcmd *xcmd, t_data *data);
void	init_export(t_export **export_arr);
t_export	*get_existing_node_position(t_data *data, char *name);

// export_utils
int	already_exists(t_data *data, char *name);
int	is_addition(char *str);
int	is_invalid(char *str);
void	init_export(t_export **export_arr);
int has_equal_sign(char *str);

// pwd
void	ft_pwd(t_xcmd *xcmd);

// unset
void	ft_unset(t_xcmd *xcmd, t_data *data);

#endif
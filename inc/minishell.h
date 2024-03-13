/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:57:03 by atudor            #+#    #+#             */
/*   Updated: 2024/03/12 15:36:15 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

//Executor
typedef struct s_data
{
	struct s_cmd	**cmd_arr;
	char			**cmd;
	char			*path;
}	t_data;

typedef struct s_cmd
{
	int		cmd_id;
	int		nr_of_cmds;
	char	**cmd;
	char	*builtin;
	char	*path;
	char	**filename_out;
	char	**filename_in;
	int		pipefd[2];
	pid_t	*pid;
}	t_cmd;

// Tokenizer
enum e_token_types
{
	space,
	text,
	variable,
	redir,
	pipe_token
};

typedef struct s_token
{
	char				*content;
	enum e_token_types	token_type;
	struct s_token		*next;
}	t_token;

// Refiner
typedef struct s_str_node
{
	char				*str;
	struct s_str_node	*next;
}	t_str_node;

typedef struct s_text_token
{
	char				*original;
	t_str_node			*expanded;
	struct s_text_token	*next;
}	t_text_token;

enum e_redir_types
{
	infile,
	outfile,
	heredoc,
	append
};

typedef struct s_redir_token
{
	enum e_redir_types		redir_type;
	t_text_token			*text_token;
	struct s_redir_token	*next;
}	t_redir_token;

typedef struct s_pipe_token
{
	int					fd_in;
	int					fd_out;
	struct s_pipe_token	*next;
}	t_pipe_token;

enum e_refined_token_types
{
	redef_text,
	redef_redir,
	redef_pipe
};

typedef struct s_refined_token
{
	enum e_refined_token_types	token_type;
	struct s_text_token			*text_token;
	struct s_redir_token		*redir_token;
	struct s_pipe_token			*pipe_token;
	struct s_refined_token		*next;
}	t_defined_token;

// Command Builder
typedef struct s_single_command
{
	t_text_token			*args;
	t_redir_token			*redirs;
	struct s_single_command	*next;
}	t_single_command;

typedef struct s_command
{
	t_single_command	*cmd_list;//
	t_pipe_token		*pipes;
}	t_command;

int		ft_strcmp(const char *line, const char *s);
int		changedir(char	**cmd);
void	execute_command(char **env, char *command);
void	exec_cmd(char **env, char *command);

#endif

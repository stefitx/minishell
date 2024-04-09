/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:57:03 by atudor            #+#    #+#             */
/*   Updated: 2024/04/05 12:14:38 by pfontenl         ###   ########.fr       */
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
# include <signal.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>


# include "./libft/libft.h"

# include "../srcs/parser/parser.h"

# include "../srcs/exec/exec.h"

# include "../srcs/env/env.h"



// int		ft_strcmp(const char *line, const char *s);
// int		changedir(char	**cmd);
// void	execute_command(char **env, char *command);
// void	exec_cmd(char **env, char *command);
// t_xcmd	**init_exe_cmd(t_command *cmd);
// void	fill_cmd(char ***xcmd, t_single_cmd *cmd);
// void	fill_path(t_xcmd *xcmd);
// void	fill_redir(t_xcmd *xcmd, t_single_cmd *cmd);
// int	check_builtin(char **xcmd);
// char	*access_path(char *argv);
// void	count_redirs(t_xcmd *xcmd, t_redir_token *parse_redir);
// void	fill_redirs(t_xcmd *xcmd, t_redir_token *parse_redir);


#endif

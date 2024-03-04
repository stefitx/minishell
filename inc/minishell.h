/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:57:03 by atudor            #+#    #+#             */
/*   Updated: 2024/03/01 14:57:45 by atudor           ###   ########.fr       */
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

typedef struct s_data
{
	struct s_cmd	**cmd_arr;
	char	**cmd;
	char	*path;
}	t_data;


typedef struct s_cmd
{
	int		cmd_id;
	int		nr_of_cmds;
	char	**cmd;
	char	*path;
	char	*filename_out;
	char	*filename_in;
	int		pipefd[2];
	pid_t	*pid;
}	t_cmd;

int	ft_strcmp(const char *line, const char *s);
int	changedir(char	**cmd);


#endif

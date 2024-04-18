/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:25:53 by atudor            #+#    #+#             */
/*   Updated: 2024/04/18 12:42:48 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "../../inc/minishell.h"
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

typedef struct s_export
{
	char	*name;
	char	*value;
	char	*str;
}	t_export;

// cd
void	ft_cd(t_xcmd *cmd, char **env);

// echo
void	ft_echo(t_xcmd *cmd);

// env

void	ft_env(t_xcmd *cmd, char **env);

// exit
void	ft_exit(t_xcmd *xcmd);

// export

// pwd

// unset

#endif
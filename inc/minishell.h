/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:57:03 by atudor            #+#    #+#             */
/*   Updated: 2024/04/18 18:28:15 by pfontenl         ###   ########.fr       */
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
# include "../srcs/built-ins/builtins.h"

#endif

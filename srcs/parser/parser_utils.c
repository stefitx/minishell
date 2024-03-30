/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:04:17 by pfontenl          #+#    #+#             */
/*   Updated: 2024/03/27 11:47:27 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*get_ifs_set(void)
{
	char	*ifs;

	ifs = getenv("IFS");
	if (!ifs)
		ifs = " \t\n";
	if (!ifs[0])
		return (NULL);
	return (ifs);
}

int	is_space_char(char c)
{
	return (ft_strchr(" \t\n", c) != NULL);
}

int	is_control_char(char c, char quote)
{
	if (quote == '\'')
		return (c == '\'');
	if (quote == '"')
		return (ft_strchr("\"$", c) != NULL);
	return (is_space_char(c) || ft_strchr("$<>|\"'", c));
}

char	*get_env(char *var)
{
	if (!var)
		return (NULL);
	if (ft_strncmp(var, "?", 2) == 0)
		return ("0");
	return (getenv(var));
}

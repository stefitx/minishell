/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_append.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 13:38:37 by pfontenl          #+#    #+#             */
/*   Updated: 2024/03/17 12:51:16 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_strappend(char **s, char *add)
{
	char	*new;
	if (!s || !add)
		return ;
	if (*s)
		new = ft_strjoin(*s, add);
	else
		new = ft_strdup(add);
	free(*s);
	*s = new;
}

// int	main(int argn, char **args)
// {
// 	int		i;
// 	char	*full;

// 	i = 1;
// 	full = NULL;
// 	while (i < argn)
// 	{
// 		ft_strappend(&full, args[i++], 0);
// 		if (i < argn)
// 			ft_strappend(&full, " ", 0);
// 	}
// 	printf("Joined args: %s\n", full);
// 	return (0);
// }

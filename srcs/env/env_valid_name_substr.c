/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_valid_name_substr.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:03:52 by pfontenl          #+#    #+#             */
/*   Updated: 2024/04/26 13:28:09 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/env.h"
#include "../../inc/minishell.h"

int	env_valid_name_substr(char *s, unsigned int start, size_t len)
{
	char	*sub;
	int		out;

	sub = ft_substr_err(s, start, len);
	out = env_valid_name(sub);
	free(sub);
	return (out);
}

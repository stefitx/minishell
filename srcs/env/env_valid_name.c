/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_valid_name.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:03:52 by pfontenl          #+#    #+#             */
/*   Updated: 2024/04/26 13:28:11 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/env.h"

int	env_valid_name(char *s)
{
	if (!s || !*s)
		return (0);
	if (ft_strncmp(s, "?", 2) == 0)
		return (1);
	if (!ft_isalpha(s[0]) && s[0] != '_')
		return (0);
	while (*++s)
		if (!ft_isalnum(*s) && *s != '_')
			return (0);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:41:04 by pfontenl          #+#    #+#             */
/*   Updated: 2023/09/21 18:41:42 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	valid_params(char const *str, unsigned int start, size_t len)
{
	size_t	i;

	if (!str || !(*str) || len == 0)
		return (0);
	i = 0;
	while (i < start)
	{
		if (!str[i])
			return (0);
		i++;
	}
	return (1);
}

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;

	if (!valid_params(str, start, len))
	{
		sub = ft_calloc(1, sizeof(char));
		if (sub)
			sub[0] = '\0';
		return (sub);
	}
	i = 0;
	while (str[i + start] && i < len)
		i++;
	sub = ft_calloc(i + 1, sizeof(char));
	if (sub)
	{
		i = 0;
		while (str[i + start] && i < len)
		{
			sub[i] = str[start + i];
			i++;
		}
		sub[i] = '\0';
	}
	return (sub);
}

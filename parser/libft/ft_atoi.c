/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:21:12 by pfontenl          #+#    #+#             */
/*   Updated: 2023/09/24 12:51:01 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	char	*cursor;
	int		sign;
	size_t	n;

	cursor = (char *)str;
	while (is_space(*cursor))
		cursor++;
	sign = 1;
	if (*cursor == '+' || *cursor == '-')
	{
		if (*cursor == '-')
			sign *= -1;
		cursor++;
	}
	n = 0;
	while (ft_isdigit(*cursor))
	{
		n *= 10;
		n += *cursor - '0';
		cursor++;
	}
	return (n * sign);
}

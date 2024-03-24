/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_chars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:57:44 by pfontenl          #+#    #+#             */
/*   Updated: 2024/01/05 12:05:46 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printf_write_char(int fd, char c)
{
	if (write(fd, &c, 1) == 1)
		return (1);
	return (-1);
}

int	printf_write_str(int fd, char const *s)
{
	int	i;

	if (!s)
		return (printf_write_str(fd, "(null)"));
	i = 0;
	while (s[i])
	{
		if (printf_write_char(fd, s[i]) == -1)
			return (-1);
		i++;
	}
	return (i);
}

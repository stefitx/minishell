/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_backend.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:00:37 by pfontenl          #+#    #+#             */
/*   Updated: 2024/01/05 12:03:21 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	eval_insert(int fd, char c, va_list args)
{
	if (!c)
		return (-1);
	if (c == 'c')
		return (printf_write_char(fd, (char)va_arg(args, int)));
	if (c == 's')
		return (printf_write_str(fd, va_arg(args, char const *)));
	if (c == 'p')
		return (printf_write_ptr(fd, va_arg(args, void *)));
	if (c == 'd' || c == 'i')
		return (printf_write_nbr(fd, va_arg(args, int)));
	if (c == 'u')
		return (printf_write_nbr_unsigned(fd, va_arg(args, unsigned int)));
	if (c == 'x' || c == 'X')
		return (printf_write_hex(fd, va_arg(args, unsigned int), c == 'X'));
	if (c == '%')
		return (printf_write_char(fd, '%'));
	if (printf_write_char(fd, '%') != 1)
		return (-1);
	if (printf_write_char(fd, c) != 1)
		return (-1);
	return (2);
}

int	write_loop(int fd, char const *s, va_list args)
{
	int	i;
	int	count;
	int	result;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '%')
			result = eval_insert(fd, s[++i], args);
		else
			result = printf_write_char(fd, s[i]);
		if (result == -1)
			return (-1);
		else
			count += result;
		if (s[i])
			i++;
	}
	return (count);
}

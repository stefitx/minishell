/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 13:06:05 by pfontenl          #+#    #+#             */
/*   Updated: 2024/01/05 12:41:28 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(char const *s, ...)
{
	va_list	args;
	int		result;

	if (!s)
		return (-1);
	if (!*s)
		return (0);
	va_start(args, s);
	result = write_loop(1, s, args);
	va_end(args);
	return (result);
}

int	ft_printf_err(char const *s, ...)
{
	va_list	args;
	int		result;

	if (!s)
		return (-1);
	if (!*s)
		return (0);
	va_start(args, s);
	result = write_loop(2, s, args);
	va_end(args);
	return (result);
}

int	ft_printf_fd(int fd, char const *s, ...)
{
	va_list	args;
	int		result;

	if (!s)
		return (-1);
	if (!*s)
		return (0);
	va_start(args, s);
	result = write_loop(fd, s, args);
	va_end(args);
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_nums.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 18:45:45 by pfontenl          #+#    #+#             */
/*   Updated: 2024/01/05 12:04:46 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printf_write_ptr(int fd, void *p)
{
	uintptr_t	ptr;
	char		*hex_chars;
	uintptr_t	i;
	int			count;

	ptr = (uintptr_t)p;
	hex_chars = "0123456789abcdef";
	i = 1;
	while (ptr / i >= 16)
		i *= 16;
	if (printf_write_str(fd, "0x") == -1)
		return (-1);
	count = 2;
	while (i > 0)
	{
		if (printf_write_char(fd, hex_chars[(ptr / i) % 16]) == -1)
			return (-1);
		count++;
		i /= 16;
	}
	return (count);
}

int	printf_write_nbr(int fd, int n)
{
	int	prev_count;
	int	count;

	if (n == -2147483648)
		return (printf_write_str(fd, "-2147483648"));
	prev_count = 0;
	count = 0;
	if (n < 0)
	{
		if (printf_write_char(fd, '-') == -1)
			return (-1);
		count++;
		n *= -1;
	}
	if (n >= 10)
	{
		prev_count = printf_write_nbr(fd, n / 10);
		if (prev_count == -1)
			return (-1);
	}
	if (printf_write_char(fd, n % 10 + '0') == -1)
		return (-1);
	count++;
	return (prev_count + count);
}

int	printf_write_nbr_unsigned(int fd, unsigned int n)
{
	int	prev_count;
	int	count;

	prev_count = 0;
	count = 0;
	if (n >= 10)
	{
		prev_count = printf_write_nbr_unsigned(fd, n / 10);
		if (prev_count == -1)
			return (-1);
	}
	if (printf_write_char(fd, n % 10 + '0') == -1)
		return (-1);
	count++;
	return (prev_count + count);
}

int	printf_write_hex(int fd, unsigned int n, int caps)
{
	char			c;
	char			*hex_chars;
	unsigned int	i;
	int				count;

	hex_chars = "0123456789abcdef";
	i = 1;
	while (n / i >= 16)
		i *= 16;
	count = 0;
	while (i > 0)
	{
		c = hex_chars[(n / i) % 16];
		if (caps && c >= 'a' && c <= 'z')
			c -= 32;
		if (printf_write_char(fd, c) == -1)
			return (-1);
		count++;
		i /= 16;
	}
	return (count);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:12:20 by pfontenl          #+#    #+#             */
/*   Updated: 2023/11/08 18:38:09 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_rows(int n)
{
	size_t	row_count;

	row_count = 1;
	if (n < 0)
	{
		n *= -1;
		row_count++;
	}
	while (n >= 10)
	{
		n /= 10;
		row_count++;
	}
	return (row_count);
}

static void	write_number(int n, char *str, size_t char_count)
{
	size_t	i;
	size_t	col_val;

	i = 0;
	if (n < 0)
	{
		str[i++] = '-';
		n *= -1;
	}
	col_val = 1;
	while (n / col_val >= 10)
		col_val *= 10;
	while (i < char_count)
	{
		str[i++] = (n / col_val) % 10 + '0';
		col_val /= 10;
	}
	str[i] = '\0';
}

char	*ft_itoa(int n)
{
	size_t	char_count;
	char	*str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	char_count = count_rows(n);
	str = ft_calloc(char_count + 1, sizeof(char));
	if (!str)
		return (NULL);
	write_number(n, str, char_count);
	return (str);
}

/*
#include <stdio.h>

int main(void)
{
    printf("----------------------\n");
    printf("> ft_itoa\n");
    printf("> 0:           '%s'\n", ft_itoa(0));
	printf("> 42:          '%s'\n", ft_itoa(42));
	printf("> -5:          '%s'\n", ft_itoa(-5));
	printf("> -132:        '%s'\n", ft_itoa(-132));
	printf("> 2147483647:  '%s'\n", ft_itoa(2147483647));
	printf("> -2147483648: '%s'\n", ft_itoa(-2147483648));
    printf("----------------------\n");
}
*/